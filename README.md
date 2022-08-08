If you want more info about BSML, you should also check out the [docs](https://redbrumbler.github.io/Quest-BSML-Docs/)

# Why I ported BSML

Since PC Mods heavily utilize BSML, to great effect, I've always thought it was a good idea to port the library to quest to truly get cross platform UI possibilities. QuestUI was always a thing we could use obviously, but it was not optimal in my opinion. It felt sluggish and honestly feels like you don't have control over the UI you create. It's also pretty difficult to see the shape of the UI when it's all just code that executes one after the other. BSML provides a better experience in that regard as you can more clearly see how things are grouped and parented without having to read a ton of code. On top of that BSML gives the possibility of more easily changing the UI during the runtime of the game, where other methods of UI would not provide this.

All this resulted in me deciding to port the library from the [PC version](https://github.com/monkeymanboy/BeatSaberMarkupLanguage) where I wanted most if not all the tags to exist in a way that we can use it on quest. Aside from some minute differences it's the same as on the pc version, so UI should be copy-pasteable now.
This means you can prototype your UI on PC, and then just copy it over to your quest, if you don't feel like constantly putting on your headset to test out your made UI. This should make creating UI for your mod a breeze.

Key differences between the PC and Quest version are that UIValues and UIActions don't exist in the same way. On quest any method on your host is handled as if it is a BSMLAction, meaning any C# method can be used as `on-click` or `on-change` actions. For BSMLValues about the same holds true, except it's fields, or methods starting with `get_` or `set_` are handled as if they are BSMLValues.

# Getting the library
To get the library, simply head over to the [releases](https://github.com/RedBrumbler/Quest-BSML/releases) section, or build it yourself.
If you want to develop with the library simply use [qpm-rust](https://github.com/RedBrumbler/QuestPackageManager-Rust) to add it as a dependency to your mod

# Building the library
To build the library, make sure you have [qpm-rust](https://github.com/RedBrumbler/QuestPackageManager-Rust) setup, as well as [ninja](https://github.com/ninja-build/ninja/releases/latest) and [cmake](https://cmake.org/download/). Powershell is also adised

```bash
git clone https://github.com/RedBrumbler/Quest-BSML.git --recursive &&
cd Quest-BSML &&
qpm-rust restore &&
cmake -G "Ninja" -DCMAKE_BUILD_TYPE="Debug" $make_docs . -B build &&
cmake --build ./build
```

You will find the binary in the `./build/` directory.

if you also want to have the `bsml.qmod` then you can also run the following commands, though these require a powershell:

```bash
qpm-rust qmod create &&
./createqmod.ps1 "BSML.qmod"
```

# Generating docs information

The mod is able to generate documentation information in the form of a json file that gets generated when you enter a song selection menu.
It's not advisable to use the docs version of the library in normal usage as this freezes the player for a couple of seconds for seemingly no good reason

To do this simply run either of the following commands in the project directory:

```shell
pwsh ./build.ps1 -docs
```
or
```shell
pwsh ./copy.ps1 -docs
```

And the compile flag for building the documentation generation will be enabled.

This will generate a json file at `/sdcard/ModData/com.beatgames.beatsaber/Mods/BSML/docs/docs.json` which will have a structure as follows:

<details>
   <summary>Object <font color="#55555">[object]</font></summary>
   <details style="margin-left:20px"><summary>tags <font color="#55555">[object array]</font></summary>
      <details style="margin-left:20px"><summary>tag <font color="#55555">[object]</font></summary>
         <p  style="margin-left:40px">
            name <font color="#55555">[string]</font><br/>
            aliases <font color="#55555">[string array]</font><br/>
            components <font color="#55555">[string array]</font>
         </p>
      </details>
   </details>
   <details style="margin-left:20px"><summary>macros <font color="#55555">[object array]</font></summary>
      <details style="margin-left:20px"><summary>macro <font color="#55555">[object]</font></summary>
         <p  style="margin-left:40px">
            name <font color="#55555">[string]</font><br/>
            aliases <font color="#55555">[string array]</font><br/>
            <details style="margin-left:20px"><summary>properties <font color="#55555">[object array]</font></summary>
               <details style="margin-left:20px"><summary>property <font color="#55555">[object]</font></summary>
                  <p  style="margin-left:40px">
                     key <font color="#55555">[string]</font><br/>
                     aliases <font color="#55555">[string array]</font>
                  </p>
               </details>
            </details>
         </p>
      </details>
   </details>
   <details style="margin-left:20px"><summary>components <font color="#55555">[object array]</font></summary>
      <details style="margin-left:20px"><summary>component <font color="#55555">[object]</font></summary>
         <p  style="margin-left:40px">
            typename <font color="#55555">[string]</font><br/>
            <details style="margin-left:20px"><summary>properties <font color="#55555">[object array]</font></summary>
               <details style="margin-left:20px"><summary>property <font color="#55555">[object]</font></summary>
                  <p  style="margin-left:40px">
                     key <font color="#55555">[string]</font><br/>
                     aliases <font color="#55555">[string array]</font>
                  </p>
               </details>
            </details>
         </p>
      </details>
   </details>
</details>

<details>
   <summary> Example Json </summary>

```json
{
    "tags": [
        {
            "name": "action-button",
            "aliases": [
                "action-button",
                "primary-button"
            ],
            "components": [
                "UnityEngine.UI.Button",
                "UnityEngine.UI.ContentSizeFitter",
                "UnityEngine.UI.LayoutElement",
                "UnityEngine.UI.LayoutGroup",
                "UnityEngine.RectTransform",
                "UnityEngine.UI.Selectable",
                "TMPro.TextMeshProUGUI"
            ]
        }
    ],
    "macros": [
        {
            "name": "macro.as-host",
            "aliases": [
                "macro.as-host"
            ],
            "properties": [
                {
                    "key": "host",
                    "aliases": [
                        "host"
                    ]
                }
            ]
        }
    ],
    "components": [
        {
            "typename": "UnityEngine.UI.Button",
            "properties": [
                {
                    "key": "clickEvent",
                    "aliases": [
                        "click-event",
                        "event-click"
                    ]
                },
                {
                    "key": "onClick",
                    "aliases": [
                        "on-click"
                    ]
                }
            ]
        }
    ]
}
```
</details>
