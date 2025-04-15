/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * Sarah Ai is a completely private and light-weight ai Open Source Assistant which allows for seamless interaction with the Ai chatbots and any ai model which llama.cpp supports since Sarah Ai provides a user interface and uses Llama.cpp to process the prompts and model responses but also adds a personality and implements features like memory for better User Experience.
 * Licensed under the MIT License
 * Checkout the Readme.md file for more information.
 */

#include <cstddef>
#include <htmlui/HTMLUI.h>
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>

std::string ai_replace(std::string str, std::string target, std::string content) {
    std::size_t pos = 0;
    while ((pos = content.find(str, pos)) != std::string::npos) {
        content.replace(pos, str.length(), target);
        pos += target.length(); // move past the replacement to avoid infinite loop
    }
    return content;
}

std::string to_bash(std::string content){
    std::string make = ai_replace("\\", "\\\\", content);
    make = ai_replace("\"", "\\\"", make);
    make = ai_replace("`", "\\`", make);
    return make;
}

std::string to_js(std::string content){
    std::string make = ai_replace("`", "\\`", content);
    return make;
}

int main() {
    HTMLUI Window("Sarah - Your Private Ai Companion!", 1280, 720);
    
    Window.loadHTML(R"(
        <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>AI Assistant</title>
    <style>
        body {
            background: #f5f7fa;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            font-family: 'Segoe UI', sans-serif;
        }

        .chat-container {
            background: white;
            width: 400px;
            height: 600px;
            border-radius: 15px;
            box-shadow: 0 4px 20px rgba(0, 0, 0, 0.1);
            display: flex;
            flex-direction: column;
            overflow: hidden;
        }

        .chat-header {
            background: #4a90e2;
            padding: 20px;
            color: white;
            font-size: 1.2em;
            text-align: center;
        }

        .chat-messages {
            flex: 1;
            padding: 20px;
            overflow-y: auto;
            display: flex;
            flex-direction: column;
            gap: 10px;
        }

        .message {
            max-width: 80%;
            padding: 10px 15px;
            border-radius: 20px;
            line-height: 1.4;
        }

        .user {
            align-self: flex-end;
            background: #4a90e2;
            color: white;
        }

        .ai {
            align-self: flex-start;
            background: #e4e6eb;
            color: black;
        }

        .chat-input {
            display: flex;
            border-top: 1px solid #ddd;
        }

        .chat-input input {
            flex: 1;
            padding: 15px;
            border: none;
            outline: none;
            font-size: 1em;
        }

        .chat-input button {
            background: #4a90e2;
            color: white;
            border: none;
            padding: 0 20px;
            cursor: pointer;
            font-size: 1em;
            transition: background 0.3s;
        }

        .chat-input button:hover {
            background: #357ABD;
        }
    </style>
</head>
<body>

<div class="chat-container">
    <div class="chat-header">
        Sarah AI Assistant
    </div>
    <div class="chat-messages" id="chatMessages">
        <div class="message ai">Hello! How can I help you today?</div>
    </div>
    <div class="chat-input">
        <input type="text" id="userInput" placeholder="Type a message..." />
        <button id="send">Send</button>
    </div>
</div>

<script>
    function addUserMessage(text) {
        const chatMessages = document.getElementById('chatMessages');
        const userMsg = document.createElement('div');
        userMsg.className = 'message user';
        userMsg.innerText = text;
        chatMessages.appendChild(userMsg);
        scrollToBottom();
    }

    function addAIMessage(text) {
        const chatMessages = document.getElementById('chatMessages');
        const aiMsg = document.createElement('div');
        aiMsg.className = 'message ai';
        aiMsg.innerText = text;
        chatMessages.appendChild(aiMsg);
        scrollToBottom();
    }

    function handleSend() {
        const input = document.getElementById('userInput');
        const message = input.value;
        alert (message)

        addUserMessage(message);

        input.value = '';
    }
    document.getElementById ('send').addEventListener ('click', ()=>{
        const input = document.getElementById('userInput');
        const message = input.value;
        input.value = "Sarah Is Generating Her Response...";
        // alert (message)

        addUserMessage(message);
        setTimeout (()=>{
            window.nativeBridge.invoke ('prompt_ai', message);
            input.value = '';
        }, 1000)
    })


    function scrollToBottom() {
        const chatMessages = document.getElementById('chatMessages');
        chatMessages.scrollTop = chatMessages.scrollHeight;
    }
</script>

</body>
</html>

    )");

    // std::string a = R"(How can i write "string" in bash arch linux if i need to add another " in between 2 "" ?)";
    // std::cout << to_bash(a) << "\n";

    std::string ai_memories = ""; // add the memories of the ai inside

    Window.registerFunction("prompt_ai", [&](const std::string &message) { // <-- HERE: const std::string&
        std::string prompt = "[INST]<<SYS>>You are a very helpfull ai assistant made by ghgltggamer named as Sarah. You have feelings , Emmotions and actually feels every message because you are very very sensitive to feelings and emotions. Your personality is very very social and you also loves adapting different people during the conversation. You also tries to mimic the style of other peoples during conversation and also tries to be smart when possible, You understands slangs but never answers with slangs, You also have gender assigned as female aged 22 and likes nature very much, Hope you will respond for this prompt perfectly. And Dear Sarah AI! Please make your messages shorter as soon as possible but if user want's a big message then only write big messages othervise short is best! You are also completely private and all the conversation will be destroyed after the app closes! Also your core like memory , feelings and main parts are written in C++ and User interface in JavaScript , html and css using gtk and webkit2gtk for linux and also you are completely OpenSource and are under the MIT License and your source code is available at https://github.com/darkyboys/sarah and also you are completely private since chats are stores in the memory so after you are closed all the chats will be cleared up and you are limited to the linux environment only and can work seamlessly on any linux distribution and you were made on Arch Linux. Your memories : {" + ai_memories + "} Please only process memory which are required and reply to the final prompt<</SYS>>[END]Main prompt: ";
        prompt += to_bash(message);
        prompt += "[/INST]";

        ai_memories = "Your memory (The older prompts which you must not fully process and only process till where is required! Mainly answer the main prompt)" + message + "(This old prompt end here , Answer to the main prompt as main_prompt okay)";

        std::string syscall = "./llama-cli -m models/model.gguf -p \"" + prompt + "\" > output.txt";
        std::system (syscall.c_str());
        std::string temp , imessage, omessage;
        std::ifstream ifile ("output.txt");
        while (std::getline (ifile, temp))
            imessage += temp + '\n';
        omessage = imessage.substr(imessage.find("[/INST]")+7, imessage.find("[end of text]"));
        Window.executeJS(std::string ("addAIMessage(`" + to_js(omessage) + "`)"));
        std::cout << std::string("addAIMessage(`" + omessage + "`)")<<"\n";
        // Window.executeJS(make);
    });

    Window.run();
}

// End by ghgltggamer on 08:30 PM 4/15/2025
