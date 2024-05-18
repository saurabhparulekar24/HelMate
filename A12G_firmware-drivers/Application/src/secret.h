#ifndef SECRET_H_decrese 
#define SECRET_H_

#define SELECT_AUTH 1
#define MAIN_WLAN_AUTH M2M_WIFI_SEC_WPA_PSK /**< Security manner */
#if(SELECT_AUTH==1)
#define MAIN_WLAN_SSID "Three Musketeers "
#define MAIN_WLAN_PSK "dunkinkamkhao"
#elif(SELECT_AUTH==2)
#define SSID "VincentSSID"
#define PWD "VincentPWD"
#endif



#endif /* SECRET_H_INCLUDED */