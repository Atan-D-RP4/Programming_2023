# importing all required python libraries
import pandas as pd
import numpy as np
from binance.client import Client
from datetime import timedelta
from datetime import datetime
import time

# creating a binance client
userkey = '4FTgsYXQqPeM3mkkkkkkkkkkk,km,jsSdkOErWO0D55PGD332iKmpGBpscviD2KRZpobhwXzwA4w79oJtO'
secretkey = 'BwToW58ufEPxMenlwlefRKotC5IO1KaQtLgf4hTfHrDJpxa3V2wDsggE4pqjCBDG'

client = Client(api_key=userkey, api_secret=secretkey)

# defining function for getting futures data


def access_futures_data(symbol, interval, limit=100):
    data = client.futures_klines(symbol=symbol, interval=interval, limit=limit)
    data = pd.DataFrame(data, columns= ['timestamp', 'open',
                                        'high', 'low', 'close', 'volume', 'close_time',
                                        'quote_asset_volume', 'number_of_trades',
                                        'taker_buy_base_asset_volume',
                                        'taker_buy_quote_asset_volume', 'ignore'])
    data['timestamp'] = pd.to_datetime(data['timestamp'], unit='ms')
    indiantime = timedelta(hours=5, minutes=30)
    data['timestamp'] = data['timestamp'] + indiantime

    return data[['timestamp', 'open',
                'high', 'low', 'close']]


print(access_futures_data('DOGEUSDT', '5m')[90::])

coins_to_track = symbol_list = ['BTCUSDT',
                                '1000BONKUSDT', '1000LUNCUSDT',
                                '1000PEPEUSDT', '1000SHIBUSDT',
                                '1INCHUSDT', 'AAVEUSDT', 'ACHUSDT',
                                'ADAUSDT', 'AGLDUSDT', 'AMBUSDT',
                                'ANKRUSDT', 'APEUSDT', 'API3USDT',
                                'APTUSDT', 'ARBUSDT', 'ARKMUSDT',
                                'ARKUSDT', 'ARPAUSDT', 'ATOMUSDT',
                                'AUDIOUSDT', 'AVAXUSDT', 'BADGERUSDT',
                                'BAKEUSDT', 'BANDUSDT', 'BCHUSDT',
                                'BELUSDT', 'BLURUSDT', 'BLZUSDT',
                                'BNBUSDT', 'BNTUSDT', 'BTCUSDT',
                                'C98USDT', 'CELOUSDT', 'CFXUSDT',
                                'CHZUSDT', 'COMPUSDT', 'CRVUSDT',
                                'CYBERUSDT', 'DODOXUSDT', 'DOGEUSDT',
                                'DOTUSDT', 'DYDXUSDT', 'EDUUSDT',
                                'EOSUSDT', 'ETCUSDT', 'ETHUSDT',
                                'FETUSDT', 'FILUSDT', 'FLMUSDT',
                                'FLOWUSDT', 'FRONTUSDT', 'FTMUSDT',
                                'GALAUSDT', 'GASUSDT', 'GMTUSDT',
                                'GRTUSDT', 'GTCUSDT', 'HBARUSDT',
                                'HIFIUSDT', 'ICXUSDT', 'IDEXUSDT',
                                'IMXUSDT', 'INJUSDT', 'IOTAUSDT',
                                'IOTXUSDT', 'JASMYUSDT', 'JOEUSDT',
                                'JTOUSDT', 'KEYUSDT', 'KLAYUSDT',
                                'KNCUSDT', 'LDOUSDT', 'LEVERUSDT',
                                'LINAUSDT', 'LINKUSDT', 'LPTUSDT',
                                'LQTYUSDT', 'LRCUSDT', 'LTCUSDT',
                                'MAGICUSDT', 'MANAUSDT', 'MASKUSDT',
                                'MATICUSDT', 'MDTUSDT', 'MEMEUSDT',
                                'MINAUSDT', 'MKRUSDT', 'MTLUSDT',
                                'NEARUSDT', 'NEOUSDT', 'NMRUSDT',
                                'OGNUSDT', 'OPUSDT', 'ORDIUSDT',
                                'OXTUSDT', 'PENDLEUSDT', 'POLYXUSDT',
                                'PYTHUSDT', 'QTUMUSDT', 'RNDRUSDT',
                                'RUNEUSDT', 'SANDUSDT', 'SEIUSDT',
                                'SFPUSDT', 'SKLUSDT', 'SNXUSDT',
                                'SOLUSDT', 'STMXUSDT', 'STORJUSDT',
                                'STXUSDT', 'SUIUSDT', 'SXPUSDT',
                                'TIAUSDT', 'TOKENUSDT', 'TRBUSDT',
                                'TRXUSDT', 'UNFIUSDT', 'UNIUSDT', 'USDCUSDT',
                                 'USTCUSDT', 'WLDUSDT', 'XLMUSDT',
                                 'XRPUSDT', 'XTZUSDT', 'XVGUSDT',
                                 'XVSUSDT', 'YFIUSDT', 'YGGUSDT',
                                 'ZRXUSDT']


def get_signal(df):
    df['open'] = pd.to_numeric(df['open'])
    df['close'] = pd.to_numeric(df['close'])

    # Add the 'signal' column
    df['signal'] = ((df['close'] - df['open']) / df['open']) * 100
    signal = df['signal'].iloc[-2]
    return signal

def find_hammer(data):
    open = float(data['open'])
    close = float(data['close'])
    high = float(data['high'])
    low = float(data['low'])
    lower_shadow = float(np.max([open, close])-low)
    upper_shadow = float(high-np.max([open, close]))
    wc = float(data['high'])-float(data['low'])
    body = float(data['high'])-float(data['low'])
    if (body/wc <= 0.25 and upper_shadow/wc <= 0.5):
        return True


def find_inverse_hammer(data):
    open = float(data['open'])
    close = float(data['close'])
    high = float(data['high'])
    low = float(data['low'])
    lower_shadow = float(np.max([open, close])-low)
    upper_shadow = float(high-np.max([open, close]))
    wc = float(data['high'])-float(data['low'])
    body = float(data['high'])-float(data['low'])
    if (body / wc <= 0.25 and lower_shadow / wc <= 0.5):
        return True


while True:
    current_minute=datetime.now().minute
    current_second=datetime.now().second
    print("---------------------------")
    if current_minute % 5 == 0:
        for i in coins_to_track:
            print(i, ": crypto pair futures data")
            print(access_futures_data(i, '5m', 100).iloc[-2])
            signalstrength = get_signal(access_futures_data(i, '5m', 100))
            if signalstrength > 2:
                print("take long position for", i)
            else signalstrength < -2:
                print("take short position for", i)
            if find_hammer(access_futures_data(i, '5m', 100).iloc[-2]) == True:
                print("hammer pattern observed in", i)
            elif find_inverse_hammer(access_futures_data(i, '5m', 100).iloc[-2]) == True:
                print("inverse hammer pattern observed in", i)
            else:
                print("no pattern observed in", i)
            print("---------------------------")
        time.sleep(100)
    elif current_minute == 10:
            exit()
