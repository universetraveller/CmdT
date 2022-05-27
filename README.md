# CmdT: A Commandline Based Tools Set  
A method  of the implementation for a simple scalable set  of command line based tools  

---
# Profile
CmdT is a command-line based tool set which contains 4 tools and an adiitional test function.  
When I have used Linux, I found the termianl and vim is excellent for works. So I try to code a similar tools set in windows and add some useful features.  
Now the demoversion of CmdT is v1.0.0 and its runtime should be Windows for its implementation.  
In the later ver it may support more features for its structure is easy to add extensions.   
Other OS such as Linux has have well-established command-line/shell/terminal based tools and it is also the inspiration of this tool.  
### The existing version (v1.0.0) includes 5 tools:  
* Command line text editor: It is a vim like text editor, but its functions are more simple and only support simply edit now.  
* Translator: Online ver and offline ver. The Online ver uses APIs to translate and the offline ver uses hash-map-dictionary to implement. (only English to Chinese offline now)  
* Private Diary: Encrypted text diary, based on users name and password. Without password, the text would be garbled code.  
* Packages Manager: For I have no server, I set a system call function to call Microsoft's Winget, a extraordinary packages manager in Windows.  
* Additional test: I set a runMtx.a file caller in the set. It is compiled in g++ in Linux for I need to test the running of it in Linux. It is a Martrix add and multiplication calculator with GPUs and uses CUDA to help accelerate.  
---  
# The files tree:  
```
.
├── bin
│   ├── ct.exe
│   └── runMtx
├── src
│   ├── include: The header files
│   ├── source: The .cpp files
│   └── CMakeList.txt
├── lib: The .dll and .a files when compiling  
├── LICENSE
└── README.md
```
# To get CmdT  
## Download in the release: https://github.com/universetraveller/CmdT/releases/tag/v1.0.0  
If you want to use CmdT, please download `ct-master.zip` and unzip it in a folder you like, then run `SetEv.exe` to set the environment variable. If successfully, you can use CmdT anywhere in terminal by `ct <parameter>`.  
If you just want a demo use, please download `Release_noEv.zip`. It would not require setting environment variable, but you should enter the unzip-folder by `cd /d path2folder` to use it.  
### Environment variable setting:  
Use `./` as your unzip folder in the following.  
* add `./bin` and `./lib` to PATH; recommand to add in users' PATH rather than system's PATH.  
---  
# To Run CmdT  
#### While you have installed ct, use it as following.  
## Basis  
* key in `ct <command> <parameters>` to use it.  
* `<command>` includes `--<long cmd>` and `-<short cmd>`, notice the counts of "-" before it.  
* `ct --version` or `ct -V` to check the version.  
*  `ct` or `ct --help` to get help information.  
## Text Editor  
usage: `ct --ed <textfile>` or `ct -e <textfile>`  
Example: `ct -e exam.txt`
then you will enter the editor.  
The operations of the editor are similar to Vim.  
The editor support 3 modes and 2 commands now, which are the simplified ver of vim.  
* In the Read-Only mode, you could use "hjkl" to control the cursor, which represents "left, down, up, right".  
* key in "i" to get insert mode and edit the text, key in "Esc" to exit the insert mode.  
* input ":" to key in command, now the editor supports 2 commadns: w(save), q(quit); you can combine them when input.  
> Existing bugs:  
> the editor does not support Syntax-highligh now for its substrate structure, if want to a syntax highlight demo, define __HIGHLIGHT__ in Editor.cpp (also have bug)  
> the cursor would get incorrect moving when the text includes full-angle characters for its implementation default is the chars are single byte.  
> Notice that the Chinese text must be UTF-8 rather than ANSI  
## Translator  
usage: `ct --ts <text>` or `ct -t <text>` with online mode, `ct --dic <text>` or `ct -T <text>` with offline mode.  
If your computer has no internet-connection, the online mode would switch to offline automatically.  
Notice that the offline mode only support English to Chinese and single word.  
Use `/exit` and `/clear` in the offline mode to control the screen buffer.  
## Private Diary  
usage: `ct --diary` or `ct -d` to enter this mode, then follow the guidance in the screen.  
If you do not have your private user account, it will create one for you.  
If you have one, it will ask you to key in your password.  
In text mode, key in a number to indicate the line you want to edit, 0 to exit.  
You could only edit single line once now(in this version), and there are 3 commands:  
* add to add a line  
* del/delete to delete a line  
* rw/rewrite to rewrite a line  
## Packages manager  
usage: `ct --list/-l` to list your applications, `ct --install/-I <package>` to install, `ct --uninstall/-U <package>` to uninstall.  
If you have no Winget in your computer, it will install one.  
So, it is better to use winget for its more and more functions...  
## Crush Matrix  
It is just a test, `ct -mtx` or `ct -m` to run it.  
Before you run it, create "A.csv" and "B.csv" and save your matrix by columns(not row!) and create a new file "result.csv"  
It is just a feature for funny, may be you also need to use it in Linux, but this tool does not support Linux.  
Not only that, the .csv would get 10GB when you successfully run it, but the most of time it consume is used on IO (may be 10min), then the main step to crush matrix only consumes 0.0003s(I only use it as middle layer, and do not write and read files), but it occupies near 10GB Gpus memory.  
how funny it is, so do not try to run it unless you really need it.   

---  
# To build CmdT  
Just download the ./src/source and ./src/lib and compile it with CMakeList file.  
If you want to edit the source code, additionally download the ./src/include which includes header files.  

---  
# Test environment  
I just test this tool in my computer, and the follow is my environment:  
### Main tests:  
* CMake: 3.21 with g++  
* IDE: Clion  
* Terminal: Microsoft Terminal  
* OS: Windows11  
### Additional Tests: 
* Ubuntu 20.04  
* Intel i9 11900K  
* CUDA 11.6  
* NVIDIA RTX A4000  
---
# References  
* cmdline: https://github.com/tanakh/cmdline  
* sion: https://github.com/zanllp/sion  
* dictionary: https://github.com/1eez/103976  
* Encryptor: https://github.com/universetraveller/simpleEncryptAlgorithm/
* Virtual-terminal: https://docs.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences  
* Winget: https://github.com/microsoft/winget-cli  
* some tips from stack overflow and microsoft-windows-api  
