//////////////////
//EEPVerManage.h
//////////////////
#ifndef _EEPVERMANAGE_H
#define _EEPVERMANAGE_H

static const int EEP_MANAGE_VER_NUM = 1; //対応するバージョンの数
static const int EEP_NUM = 12;			 //EEPの数

typedef enum 
{
    EEP_MANAGE_VER_FIRST = 0,  // 初期バージョン
   
} EEP_MANAGE_VER;

static const int TEMPLATE_RES_IDs[EEP_MANAGE_VER_NUM][EEP_NUM] = 
{
	//初期バージョン
	{
		IDR_TEMPL_8011 ,
		IDR_TEMPL_8012 ,
		IDR_TEMPL_8013 ,
		IDR_TEMPL_8014 ,
		IDR_TEMPL_8015 ,
		IDR_TEMPL_8016 ,
		IDR_TEMPL_8017 ,
		IDR_TEMPL_8018 ,
		IDR_TEMPL_8019 ,
		IDR_TEMPL_8020 ,
		IDR_TEMPL_8021 ,
		IDR_TEMPL_8022 ,
	}
	, 
};

#endif /* _EEPVERMANAGE_H */