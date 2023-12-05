#include "BSML/Animations/GIF/GifDecoder.hpp"
#include "logging.hpp"

#include "Helpers/delegates.hpp"

#include "System/Threading/Tasks/Task.hpp"
#include "System/Func_1.hpp"
#include "System/Func_1.hpp"
#include "UnityEngine/WaitUntil.hpp"

#include "gif-lib/shared/gif_lib.h"

#include "EasyGifReader.h"

#define SIMPLE_CASE(enum_case) case enum_case: return #enum_case

std::string errToString(const EasyGifReader::Error& err) {
    switch (err) {
        using EasyGifReader::Error;

        default: [[fallthrough]]
        SIMPLE_CASE(UNKNOWN);
        SIMPLE_CASE(INVALID_OPERATION);
        SIMPLE_CASE(OPEN_FAILED);
        SIMPLE_CASE(READ_FAILED);
        SIMPLE_CASE(INVALID_FILENAME);
        SIMPLE_CASE(NOT_A_GIF_FILE);
        SIMPLE_CASE(INVALID_GIF_FILE);
        SIMPLE_CASE(OUT_OF_MEMORY);
        SIMPLE_CASE(CLOSE_FAILED);
        SIMPLE_CASE(NOT_READABLE);
        SIMPLE_CASE(IMAGE_DEFECT);
        SIMPLE_CASE(UNEXPECTED_EOF);
    }
}

/// @brief makes RGB (0, 0, 0) into transparent pixels
inline uint32_t make_black_transparent(const uint32_t& v) {
    return v >> 8 ? v : 0;
}

namespace BSML {

    custom_types::Helpers::Coroutine GifDecoder::Process(ArrayW<uint8_t> data, std::function<void(AnimationInfo*)> onFinished) {
        co_yield custom_types::Helpers::CoroutineHelper::New(Process(data, onFinished, [](){
            ERROR("Unhandled gif processing error ocurred!");
        }));
        co_return;
    }

    custom_types::Helpers::Coroutine GifDecoder::Process(ArrayW<uint8_t> data, std::function<void(AnimationInfo*)> onFinished, std::function<void()> onError) {
        auto animationInfo = new AnimationInfo();
        auto taskDelegate = MakeSystemAction(
            [data, animationInfo, onError]() {
                GifDecoder::ProcessingThread(data, animationInfo, onError);
            }
        );

        System::Threading::Tasks::Task::Run(taskDelegate);

        while (!animationInfo->isInitialized) co_yield nullptr;

        if (onFinished)
            onFinished(animationInfo);
        else
            ERROR("Nullptr onFinished given!");
        co_return;
    }

    void GifDecoder::ProcessingThread(ArrayW<uint8_t> gifData, AnimationInfo* animationInfo) {
        ProcessingThread(gifData, animationInfo, [](){
            ERROR("Unhandled Gif Processing Error ocurred!");
        });
    }

    void GifDecoder::ProcessingThread(ArrayW<uint8_t> gifData, AnimationInfo* animationInfo, std::function<void()> onError) {
        DEBUG("Open gif");
        try {
            auto gifReader = EasyGifReader::openMemory(gifData.begin(), gifData.size());
            int width = gifReader.width(), height = gifReader.height(), frameCount = gifReader.frameCount();

            animationInfo->frameCount = frameCount;
            animationInfo->frames.reserve(frameCount);
            animationInfo->isInitialized = true;

            DEBUG("iterating gif frames");
            for (const auto& gifFrame : gifReader) {
                auto currentFrame = new FrameInfo(gifFrame.width(), gifFrame.height());

                const uint8_t* pixels = (const uint8_t*)gifFrame.pixels();
                // get end of the data
                uint8_t* colorData = currentFrame->colors.ptr()->values + currentFrame->colors.ptr()->Length();
                int height = gifFrame.height();
                int rowSize = sizeof(uint32_t) * gifFrame.width();
                // we need to iterate the given data in reverse due to unity's texture system
                for (int y = 0; y < height; y++) {
                    // pre-decrement because we start at end of data
                    colorData -= rowSize;
                    // just copy all the data as is
                    //memcpy(colorData, pixels, rowSize);
                    // make black pixels transparent
                    std::transform((uint32_t*)pixels, (uint32_t*)(pixels + rowSize), (uint32_t*)colorData, make_black_transparent);
                    pixels += rowSize;
                }

                // delay in millis
                currentFrame->delay = gifFrame.rawDuration().milliseconds();
                // add to end of vector
                animationInfo->frames.emplace_back(currentFrame);
            }
        } catch (EasyGifReader::Error gifError) {
            ERROR("Gif error: {}", errToString(gifError));
            if (onError) onError();
        }
    }
}
