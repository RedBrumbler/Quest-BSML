#include "BSML/Components/ButtonIconImage.hpp"
#include "Helpers/utilities.hpp"

DEFINE_TYPE(BSML, ButtonIconImage);

void BSML::ButtonIconImage::SetIcon(StringW path) {
    if (image) Utilities::SetImage(image, path);
}

void BSML::ButtonIconImage::SetIcon(UnityEngine::Sprite sprite) {
    if (image) image.sprite = sprite;
}

UnityEngine::Sprite get_Icon() {
    return image ? image.sprite : UnityEngine::Sprite(nullptr);
}
void set_Icon(UnityEngine::Sprite icon) {
    SetIcon(icon);
}
