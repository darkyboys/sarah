# Sarah Ai - A Truly Private Ai For Everyone
Sarah Ai is a personality driven yet completely private ai assistant written using C++, JavaScript, Html and css with the help of gtk3+ and webkit2gtk and LlaMa.cpp project for making a very private locally hosted infinite solution for the users.

Sarah Ai is also completely Open Source and is under the MIT License , Also note that Sarah Ai don't itself provides the LlaMa.cpp with it , Yet it uses magma build system to install it locally and compile entire project on your linux machiene.

Sarah Ai has such advanced features like One-Time-Chat-Memory (OTCM) & Feelings , Emotions etc. All for free and no one can spy on you.

Sarah Ai was written by ghgltggamer in his 16 years old age as a fun project and any can use, modify and even sell it for any purpose but for any illegal use no one including ghgltggamer is not responsible, Except you yourself.

Sarah Ai don't comes with any censorships since , Sarah Ai is just an engine to run Ai but you will need a model to make Sarah Ai react and response, Prefered model is LlaMa 7B Chat 8_0 GUFF which you can [get here](https://huggingface.co/TheBloke/Llama-2-7B-Chat-GGUF/resolve/main/llama-2-7b-chat.Q8_0.gguf) and load the model.


## Installation
Sarah Ai is only for linux so installation is for linux based computers only.

### Dependencies 
Before you install sarah ai make sure that you have the following things installed in your system.
 - Gtk3+
 - Webkit2Gtk4
 - GNU GCC/G++
 - Cmake 
 - Make
 - Git
 - Magma [get it here](https://github.com/darkyboys/magma)

Once you have these Dependencies you can follow up the installation next!

## Install Process
Install by cloning the repository
```bash
git clone https://github.com/darkyboys/sarah.git
cd sarah
```
---
#### Resolving Dependencies

Now once in the clone repository, You will need to resolve the dependencies of Sarah Ai like installing the llama.cpp because currently you only have the build configuration but you still need to build the project so don't worry we will be using magma build system for it.

First let's resolve the dependencies by executing.
```bash
sudo magma resolve
```
This will resolve all dependencies like making llama.cpp , make config etc

---

#### Making the main project
Now once dependencies are resolved it's time to make the main project so just run.
```bash
sudo magma make
```
This will not just make but also run the application once, But don't enter any prompts because now you have the main project builded but no Ai model to run, So you must install an Ai model first before using any prompts to ignore any unexected issues.

Currently the project is built inside the new `sarah` directory which will be containing llama.cpp binaries and libraries but also `Sarah` binary of the project which is the entire UI.

---

#### Get the default model
Sarah Ai also has default model configurations , Like if you run
```bash
sudo magma get_model
```
then it will automatically download and setup the default LlaMa 7B 8_0 model which is 7GB+ larger in size. for any custom model make sure to download the guff file and place it inside the sarah/models directory named as model.guff for sarah to load it.

--- 

### Contributing ?
Check out the [CONTRIBUTING.md](CONTRIBUTING.md)

Written by ghgltggamer 
thanks you

---

Copyright (c) ghgltggamer 2025 (01:08 AM 04/15/2025)
