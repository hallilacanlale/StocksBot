import pandas as pd
import yfinance as yf
from yahoofinancials import YahooFinancials
import time
import serial
import serial.tools.list_ports
from csv import writer


class Stock:
  def __init__(self, stock, count, price, buy): 
    self.stock = stock 
    self.count = count
    self.price = price
    self.buy = True


portfolio = []
# Samples
portfolio.append(Stock("AAPL", 21, 167.4, True))
portfolio.append(Stock("TSLA", 10, 1028.15, False))




ser = serial.Serial('/dev/cu.usbmodem143201', 9600)
time.sleep(2)


flag = False
while flag == False:
  if (ser.read() == b'y'):
    for stock in portfolio:
      ser.write(b'2')
      ser.write(stock.stock + ": ~" + stock.count + ',' + stock.price)
      time.sleep(.1)

      ser.write(stock.stock + ": ~")
      ser.write(int(stock.count).to_bytes(1, 'big'))
      ser.write(int(stock.prince).to_bytes(2, 'big'))

      #  ser.write(name + ': *' + share.get_open()+','+share.get_price())
      # print name + ': *' + share.get_open()+','+share.get_price()
      # time.sleep(.1)

      # ser.write(int(price).to_bytes(2, 'big'))
      # ser.write(int((price%1)*100).to_bytes(1, 'big'))
      # ser.write(int(closePrice[count]).to_bytes(2, 'big'))
      # ser.write(int((closePrice[count]%1)*100).to_bytes(1, 'big'))


    flag = True
  # print(ser.read().rstrip('\r\n').decode("utf-8"))



tickerSymbol = input("Enter Ticker Symbol: ")
numStocks = input("Enter Number of Stocks: ")


# ##
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

  test_val = [50, 73, 60, 31, 28]

  # for curr_res_val in test_val:
  # print(curr_res_val)

  #this is where to check if button1 is pressed
  if (curr_res_val <= 30):
    print ("buy signal")
    portfolio.append(Stock(tickerSymbol, numStocks, curr_res_val, True))

  elif (curr_res_val >= 70): 
    print ("sell signal")
    portfolio.append(Stock(tickerSymbol, numStocks, curr_res_val, False))




# # test val:
# test_val = [50, 73, 60, 31, 28]

# for curr_res_val in test_val:
#   print(curr_res_val)

#   if (curr_res_val <= 30):
#     print ("buy signal")
#     portfolio.append(Stock(tickerSymbol, numStocks, curr_res_val, True))

#   elif (curr_res_val >= 70): 
#     print ("sell signal")
#     portfolio.append(Stock(tickerSymbol, numStocks, curr_res_val, False))
  

