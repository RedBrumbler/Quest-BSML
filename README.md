# Why this?

I was kinda bored and thought a (possibly non-complete) port of BSML might be very useful for quest mods despite probably objections by some people.

also I was wondering how difficult it would be to make it work and turns out not too difficult

# Building it

Clone the repo

```bash
git clone https://github.com/RedBrumbler/Quest-BSML.git --recursive &&
cd Quest-BSML &&
qpm-rust restore &&
pwsh ./build.ps1
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
