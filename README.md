# Studies on Ocornut ImGUI Demo adapted to Webassembly
My studies and coding about @github/ocornut imgui demo in Webassembly

## Previous on my delirious:

* I want very much learn WebAssembly
  * Finally, I found some demonstration having a GUI to study

* [Original demo](http://sol.gfxile.net/ocornut_demo/imgui.html)
  * If you remove the imgui.html from the above URL, you could list the files on ocornut_demo path
  * There, there are the final product which is the html, mem file and js
  * But there are the source that generated the page

* Now, I will put here all my modifications on that code..
   * To start, the __first commit__ is the code of @github/ocornut in this link (above)

* **Thanks** to @github/ocornut to provide this demonstration

## Requirements
* Just install [Webassembly toolchain](http://webassembly.org/getting-started/developers-guide/)
  * Run the bash script


### History
#### 2017-10-24

* Second commit
  * The original source

* Third commit starts my *modifications*, *fixes*...
  * Some aesthetics modifications on folder structure
  * An bash script to compile
    * I try __cmake__, but it not find Webassembly toolchain
    * Could not make it with __make__
    * Bash __rules__ :wink:

* Update code to ImGUI 1.51
  * I just added/replaced the code where it's needed
    *  modifications on imgui_impl_sdl.cpp file
