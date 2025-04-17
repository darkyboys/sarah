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
  <title>Sarah AI Assistant</title>
  <style>
    :root {
      --glass-bg: rgba(255, 255, 255, 0.2);
      --blur: blur(15px);
      --pastel-purple: #e0bbff;
      --pastel-pink: #ffd6e8;
      --pastel-yellow: #fff4b8;
      --pastel-blue: #d6f0ff;
      --ai-color: #fbeeff;
      --user-color: #c7f2ff;
      --font: 'Segoe UI', sans-serif;
    }

    body {
      margin: 0;
      height: 100vh;
      display: flex;
      justify-content: center;
      align-items: center;
      font-family: var(--font);
      background: linear-gradient(135deg, #ffe9f3, #e3f6ff, #fff9e8);
      background-size: 400% 400%;
      animation: backgroundFlow 15s ease infinite;
    }

    .chat-container {
      width: 650px;
      height: 700px;
      border-radius: 30px;
      backdrop-filter: var(--blur);
      background: var(--glass-bg);
      box-shadow: 0 8px 32px rgba(0, 0, 0, 0.2);
      display: flex;
      flex-direction: column;
      overflow: hidden;
      border: 2px solid rgba(255, 255, 255, 0.3);
      animation: popIn 0.6s ease;
    }

    .chat-header {
      background: linear-gradient(to right, #f9caff, #ffd1dc);
      color: #4b0082;
      padding: 30px;
      text-align: center;
      font-size: 1.8em;
      font-weight: bold;
      border-bottom: 1px solid rgba(255, 255, 255, 0.2);
    }

    .chat-messages {
      flex: 1;
      padding: 25px;
      overflow-y: auto;
      display: flex;
      flex-direction: column;
      gap: 15px;
      animation: fadeIn 1s ease;
    }

    .message {
      max-width: 85%;
      padding: 18px 25px;
      border-radius: 20px;
      font-size: 1.2em;
      line-height: 1.6;
      backdrop-filter: blur(5px);
      box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
      transition: transform 0.3s ease;
    }

    .user {
      align-self: flex-end;
      background: var(--user-color);
      color: #1b2a49;
    }

    .ai {
      align-self: flex-start;
      background: var(--ai-color);
      color: #4b0082;
    }

    .chat-input {
      display: flex;
      border-top: 1px solid rgba(255, 255, 255, 0.2);
      padding: 15px;
      background: rgba(255, 255, 255, 0.15);
      backdrop-filter: blur(10px);
    }

    .chat-input input {
      flex: 1;
      padding: 18px;
      border: none;
      outline: none;
      border-radius: 15px;
      font-size: 1.2em;
      background: rgba(255, 255, 255, 0.3);
      color: #4b0082;
      transition: box-shadow 0.3s ease;
    }

    .chat-input input:focus {
      box-shadow: 0 0 0 2px #f9caff;
    }

    .chat-input button {
      background: linear-gradient(to right, #f9caff, #ffd1dc);
      color: #4b0082;
      border: none;
      border-radius: 15px;
      margin-left: 15px;
      padding: 0 25px;
      cursor: pointer;
      font-size: 1.2em;
      transition: transform 0.2s ease, background 0.3s ease;
    }

    .chat-input button:hover {
      background: linear-gradient(to right, #fbb1ff, #ffc8d8);
      transform: scale(1.05);
    }

    /* Animations */
    @keyframes fadeIn {
      from { opacity: 0; transform: translateY(10px); }
      to { opacity: 1; transform: translateY(0); }
    }

    @keyframes popIn {
      0% { transform: scale(0.95); opacity: 0; }
      100% { transform: scale(1); opacity: 1; }
    }

    @keyframes backgroundFlow {
      0% { background-position: 0% 50%; }
      50% { background-position: 100% 50%; }
      100% { background-position: 0% 50%; }
    }

    /* Scrollbar styling for ✨aesthetic✨ */
    ::-webkit-scrollbar {
      width: 8px;
    }
    ::-webkit-scrollbar-track {
      background: transparent;
    }
    ::-webkit-scrollbar-thumb {
      background: #f9caff;
      border-radius: 8px;
    }

    /* Responsive Layout */
    @media (max-width: 768px) {
      .chat-container {
        width: 90%;
        height: 600px;
      }
      .chat-header {
        font-size: 1.4em;
        padding: 20px;
      }
      .chat-messages {
        padding: 15px;
      }
      .message {
        max-width: 90%;
        padding: 12px 18px;
        font-size: 1em;
      }
      .chat-input input {
        font-size: 1em;
      }
      .chat-input button {
        padding: 0 20px;
        font-size: 1em;
      }
    }
  </style>
</head>
<body>

<div class="chat-container">
  <div class="chat-header">
    Sarah AI Assistant 🌸
  </div>
  <div class="chat-messages" id="chatMessages">
    <div class="message ai">Hello! How can I help you today? 🌼</div>
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

  document.getElementById('send').addEventListener('click', () => {
    const input = document.getElementById('userInput');
    const message = input.value;
    input.value = "Sarah Is Generating Her Response...";
    addUserMessage(message);
    setTimeout(() => {
      window.nativeBridge.invoke('prompt_ai', message);
      input.value = '';
    }, 1000);
  });

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
