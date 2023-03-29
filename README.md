# CyberTrade: Stocks Bot

CyberTrade allows stock traders to buy, sell, and trade stocks automatically using a bot that executes trades based on a specific trading strategy, with the goal of automating profits. It utilizes electric components such as Arduino and RFID card.

Goal: To increase revenue and reduce losses and risks with as little work from the user as possible

## How does it work?

This code for this bot can be broken into 3 different parts:

1. Web scrapes active stocks from yahoo finance.
2. Evaluates active stocks (can evaluate 100s of stocks per minute as the application is multithreaded) using RSI breakthroughs.
3. Evaluates current stock portfolio by checking if any stock no longer seems worth holding.
4. Sends buy and sell requests

That's it!

<img width="488" alt="image" src="https://user-images.githubusercontent.com/57775171/228615349-6abda4a6-3681-4217-ac70-c8345683f445.png">
