import pandas as pd
import yfinance as yf
from yahoofinancials import YahooFinancials
import time
import serial
import serial.tools.list_ports

ser = serial.Serial('COM9', 9600)
time.sleep(2)

tickerSymbol=input("Enter Ticker Symbol: ")

##
def rsi(df, window):
    print(type(df))
    diff = df.loc[:,'Close'].diff().tail(28)

    up = diff.clip(lower=0)
    down = -1 * diff.clip(upper=0)
    
    ma_up = up.ewm(com = window - 1, min_periods = window).mean()
    ma_down = down.ewm(com = window - 1, min_periods = window).mean()

    rs = abs(ma_up/ma_down)
    rsi = 100 - 100/(1+rs)
    return rsi



while True:
  print()
  data = yf.download(
        tickers = tickerSymbol,
        period = "1d", # user_input
        interval = "1m", 
        group_by = 'ticker',
        auto_adjust = True)
  print((data.loc[:,"Close"].tail(14)))
  res = rsi(data, 14)
  prev_res_val = res.iat[-2]
  curr_res_val = res.iat[-1]

  print(prev_res_val)
  print(curr_res_val)


  if (curr_res_val <= 30):
    print ("buy signal, buzzer")
  elif (curr_res_val >= 70): 
    print ("sell signal, buzzer")

  if (prev_res_val > curr_res_val):
    # red
    ser.write(b'1')
    time.sleep(5)
  elif (prev_res_val < curr_res_val):
    # greem
    ser.write(b'0')
    
  time.sleep(60)

  res = rsi(data, 14)
  print(res)
  prev_res_val = res.iat[-2]
  curr_res_val = res.iat[-1]

  print(prev_res_val)
  print(curr_res_val)

  if (curr_res_val <= 30):
    print ("buy signal")
  elif (curr_res_val >= 70): 
    print ("sell signal")





