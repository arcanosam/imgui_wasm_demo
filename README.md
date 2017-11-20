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
   * To start, the __second commit__ is the code of @ocornut (source link above)

* **Thanks** to @ocornut to provide this demonstration

## Requirements
* Just install [Webassembly toolchain](http://webassembly.org/getting-started/developers-guide/)

## Usage
  * Open console/prompt command
    * Run: *source __[[path to emsdk folder]]__/emsdk_env.sh*
  * Clone this repo
    * git clone https://github.com/arcanosam/imgui_wasm_demo
  * Access repo folder
  * Run *./app/build.sh*
    * Don't forget permissions on build script
      * *chmod +x ./app/build.sh*
    * At end, will be generated all files on *./html* folder
    * Open up html file on your browser (Chrome or Firefox)
      * Both browsers must be updated for having *Webassembly* enabled by default


### History

#### 2017-10-20

* Just rename console error on Firefox
  * Adding Chrome console
  * See it here: [Chrome console log text](https://github.com/arcanosam/imgui_wasm_demo/blob/master/chrome_console_20171120.md)
    * Better crash handle. I didn't have to force a restart on my CentOS 7
    * Problem persist, lost the link with shader pogram which lead us at CONTEXT_LOST_WEBGL.
      * I admit not having much time to pursue a solution

#### 2017-10-27

* First draft
  * _compiling_: __ok__
  * _running_: for a while until __crash__ - :boom:
    * be alert when running on browser
  * __main.cpp__
    * I'm trying to list only the __essential__ code to make a simple background with color
    * The crash on execution it's seems because the 'link' with the shader program is lost somehow
    * See [Firefox console log text](https://github.com/arcanosam/imgui_wasm_demo/blob/master/firefox_console_20171027.md)
  * __tpl.html__
    * My version of template html used to generated the final product.
    * Same idea: only the __essential__ to load the application.
* Move __html__ folder to root of repo
* Add the parameter to use my html template on _build.sh_ script

#### 2017-10-25

* Release 0.0.1 launched

* Update Readme.md instructions
  * Added *Usage* section

* Changes on build bash script
  * I added the parameters below (see them in *emcc --help*):
    * *--separate-asm* ($EMSASMJS)
      * Separate asm.js file from your codes
    * *-g4* ($EMSDEBUG)
      * Include debug symbols and unminify both Js codes generated

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
      *  retrieve from 1.47 version of the same imgui_impl_sdl.cpp
