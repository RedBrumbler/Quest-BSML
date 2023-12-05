#include "BSML/Animations/AnimationLoader.hpp"
#include "BSML/Animations/GIF/GifDecoder.hpp"
#include "logging.hpp"

#include "UnityEngine/SystemInfo.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/WaitUntil.hpp"
#include "UnityEngine/TextureWrapMode.hpp"
#include "UnityEngine/ImageConversion.hpp"
#include "System/IO/File.hpp"

#include "Helpers/delegates.hpp"

#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "System/Func_1.hpp"

DEFINE_TYPE(BSML, AnimationLoader);


namespace BSML {
    int get_atlasSizeLimit() {
        using GetMaxTextureSize = function_ptr_t<int>;
        static auto getMaxTextureSize = reinterpret_cast<GetMaxTextureSize>(il2cpp_functions::resolve_icall("UnityEngine.SystemInfo::GetMaxTextureSize"));
        static int maxSize = getMaxTextureSize ? getMaxTextureSize() : 4096;
        return maxSize >= 4096 ? 4096 : maxSize;
    }

    void AnimationLoader::Process(AnimationType type, ArrayW<uint8_t> data, std::function<void(UnityEngine::Texture2D, ArrayW<UnityEngine::Rect>, ArrayW<float>)> onProcessed) {
        Process(type, data, onProcessed, [](){
            ERROR("Error happened while processing Animation, and error was not handled!");
        });
    }

    void AnimationLoader::Process(AnimationType type, ArrayW<uint8_t> data, std::function<void(UnityEngine::Texture2D, ArrayW<UnityEngine::Rect>, ArrayW<float>)> onProcessed, std::function<void()> onError) {
        // FIXME: is shared starter still a thing?
        auto sharedStarter = GlobalNamespace::SharedCoroutineStarter::get_instance();
        DEBUG("Starting animation decode");
        switch (type) {
            case AnimationType::GIF:
                sharedStarter.StartCoroutine(custom_types::Helpers::CoroutineHelper::New(
                    GifDecoder::Process(
                        data,
                        [sharedStarter, onProcessed](auto animationInfo){
                            DEBUG("Processed Data, processing animation info");
                            sharedStarter.StartCoroutine(custom_types::Helpers::CoroutineHelper::New(ProcessAnimationInfo(animationInfo, onProcessed)));
                        },
                        onError
                    )));
                break;
            case AnimationType::APNG:
                // TODO: implement APNG support at some point?
                if (onError) onError();
                break;
            default:
                break;
        }
    }

    custom_types::Helpers::Coroutine AnimationLoader::ProcessAnimationInfo(AnimationInfo* animationInfo, std::function<void(UnityEngine::Texture2D, ArrayW<UnityEngine::Rect>, ArrayW<float>)> onProcessed) {
        DEBUG("ProcessAnimInfo");
        int textureSize = get_atlasSizeLimit(), width = 0, height = 0;
        UnityEngine::Texture2D texture{nullptr};
        auto textureList = ArrayW<UnityEngine::Texture2D>(animationInfo->frameCount);
        ArrayW<float> delays = ArrayW<float>(animationInfo->frameCount);

        float lastThrottleTime = UnityEngine::Time::get_realtimeSinceStartup();

        for (int i = 0; i < animationInfo->frameCount; i++) {
            DEBUG("Frame {}", i);
            // while size less than or equal to i, wait
            bool throttled = false;
            while (animationInfo->frames.size() <= i) {
                co_yield nullptr;
                throttled = true;
            }
            if (throttled) lastThrottleTime = UnityEngine::Time::get_realtimeSinceStartup();
            auto& currentFrameInfo = animationInfo->frames.at(i);

            if (!texture) {
                textureSize = GetTextureSize(animationInfo, i);

                width = currentFrameInfo->width;
                height = currentFrameInfo->height;
                texture = UnityEngine::Texture2D::New_ctor(width, height);
            }

            delays[i] = currentFrameInfo->delay;

            auto frameTexture = UnityEngine::Texture2D::New_ctor(currentFrameInfo->width, currentFrameInfo->height, UnityEngine::TextureFormat::RGBA32, false);
            frameTexture.wrapMode = UnityEngine::TextureWrapMode::Clamp;
            frameTexture.LoadRawTextureData(currentFrameInfo->colors.ptr());

            textureList[i] = frameTexture;

            if (UnityEngine::Time::get_realtimeSinceStartup() > lastThrottleTime + 0.0005f) {
                co_yield nullptr;
                lastThrottleTime = UnityEngine::Time::get_realtimeSinceStartup();
            }

            // cleanup as we go
            delete currentFrameInfo;
            currentFrameInfo = nullptr;
        }

        // note to self, no longer readable = true means you can't encode the texture to png!
        auto atlas = texture.PackTextures(textureList, 2, textureSize, true);

        // cleanup
        for (auto t : textureList) {
            if (t && t.m_CachedPtr.m_value)
                UnityEngine::Object::DestroyImmediate(t);
        }

        if (onProcessed)
            onProcessed(texture, atlas, delays);

        // we are now done with the animation info
        delete animationInfo;
        co_return;
    }

    int AnimationLoader::GetTextureSize(AnimationInfo* animationInfo, int i) {
        int testNum = 2, numFramesInRow = 0, numFramesInColumn = 0;

        while (true) {
            int numFrames = animationInfo->frameCount;

            if ((numFrames % testNum) != 0) {
                numFrames += numFrames % testNum;
            }

            numFramesInRow = std::max(numFrames / testNum, 1);
            numFramesInColumn = numFrames / numFramesInRow;
            if (numFramesInRow <= numFramesInColumn) break;
            testNum += 2;
        }

        int textureWidth = std::clamp(numFramesInRow * animationInfo->frames[i]->width, 0, get_atlasSizeLimit());
        int textureHeight = std::clamp(numFramesInColumn * animationInfo->frames[i]->height, 0, get_atlasSizeLimit());
        return std::max(textureWidth, textureHeight);
    }
}
