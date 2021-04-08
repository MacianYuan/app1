
/****************************Copyright(c)*****************************************
*                         北京南瑞智芯微电子科技                                  
*                              通信控制业务                                       
*--------------------------------FileInfo-----------------------------------------
*@File Name: Utils.c
*@Last modified Date: 2014-7-23               //完成日期
*@Last Version:                                          //版本信息
*@Cread By: HZF                                   //作者
*@Modified by:                                         //修改者
*@Modified Time:                                       //修改时间
*@brief: for all the modules                           //描述
**********************************************************************************
*@note 
* 
* 
* 
* 
* 
*********************************************************************************/


//文件头注释

macro InsertFileHeader()
{
	//szMyName = getenv(MYNAME)
	

	hbuf = GetCurrentBuf()
	ProgEnvInfo=GetProgramEnvironmentInfo()
	Author=ProgEnvInfo.UserName
	
	LocalTime =GetSysTime(1)
	Year=LocalTime.Year
	Month=LocalTime.Month
	Day=LocalTime.Day

	szBufName=GetBufName(hbuf)
	Len=strlen(szBufName)
	FileName=""
	if(0!=Len)
	{
		cch=Len
		while("\\"!= szBufName[cch])
		{
			cch=cch-1
		}

		while(cch<Len)
		{
			cch=cch+1
			FileName= Cat(FileName,szBufName[cch])
			//Msg("@FileName@")
		}
	}

	ln=1
	
	InsBufLine(hbuf,ln,"/*********************************Copyright(c)************************************")
	ln=ln+1
	InsBufLine(hbuf,ln,"*                         北京智芯微电子科技有限公司                          ")
	ln=ln+1
	InsBufLine(hbuf,ln,"*                              通信控制事业部                                      ")
	ln=ln+1
	InsBufLine(hbuf,ln,"*--------------------------------FileInfo-----------------------------------------")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@File Name: @FileName@")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@Last modified Date: @Year@-@Month@-@Day@               //完成日期")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@Last Version:1.0.1                                     //版本信息")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@Cread By: @Author@                                   //作者")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@Modified by:                                         //修改者")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@Modified Time:                                       //修改时间")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@brief: for all the modules                           //描述")
	ln=ln+1
	InsBufLine(hbuf,ln,"**********************************************************************************")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@note ")
	ln=ln+1
	InsBufLine(hbuf,ln,"* ")
	ln=ln+1
	InsBufLine(hbuf,ln,"* ")
	ln=ln+1
	InsBufLine(hbuf,ln,"* ")
	ln=ln+1
	InsBufLine(hbuf,ln,"* ")
	ln=ln+1
	InsBufLine(hbuf,ln,"* ")
	ln=ln+1
	InsBufLine(hbuf,ln,"*********************************************************************************/")
	ln=ln+1

	SetBufIns(hbuf,ln,0)
	Len=strLen(FileName)
	if(("h" == tolower(FileName[Len-1])) && ("."== FileName[Len-2]))
	{
		FileName = toupper(FileName)
		FileName[Len-2]="_"
		szDef ="__"
		szDef=Cat(szDef,FileName)
		szDef=Cat(szDef,"__")

		ProgEnvInfo = GetProgramEnvironmentInfo()
		Editor =ProgEnvInfo.UserName

		hwnd=GetCurrentWnd()
		ln=GetWndSelLnFirst(hwnd)
		LocalTime =GetSysTime(1)
		Year=LocalTime.Year
		Month=LocalTime.Month
		Day=LocalTime.Day
		Time=LocalTime.Time
		hbuf=GetCurrentBuf()
		InsBufLine(hbuf,ln,"#ifndef @szDef@")
		ln=ln+1
		InsBufLine(hbuf,ln,"#define @szDef@")
		ln=ln+1
		InsBufLine(hbuf,ln,"")
		ln=ln+1
		InsBufLine(hbuf,ln,"")
		ln=ln+1
		InsBufLine(hbuf,ln,"")
		ln=ln+1
		InsBufLine(hbuf,ln,"#endif  /*ifndef @szDef@.@Year@-@Month@-@Day@ @Time@ @Editor@*/")
		ln=ln+1
	}

	SaveBuf(hbuf)
}



/**********************************************************************************
*@FuncName :InsertComment			//函数名称
*@brief 
* 添加单行注释
* 
*@Para[in] : 				//参数输入
*@Para[out] : 				//参数输出
*@return :					//返回值 
*@note :						//注解
*********************************************************************************/
macro InsertComment()
{
	sz=Ask("Enter Comment:")
	if(sz!= "")
	CommentSz(sz)
}

macro CommentSz(sz)
{
	hbufCur = GetCurrentBuf()
	SetBufSelText(hbufCur,"//!@sz@")
}


/**********************************************************************************
*@FuncName :InsertFunctionHeader			//函数名称
*@brief 
* 
* 
*@Para[in] : 				//参数输入
*@Para[out] : 				//参数输出
*@return :					//返回值 
*@note :						//注解
*********************************************************************************/
macro InsertFunctionHeader()
{
	hbuf=GetCurrentBuf()
	ln=GetBufLnCur(hbuf)
	FuncName = GetCurSymbol()

	InsBufLine(hbuf,ln,"/**********************************************************************************")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@FuncName :@FuncName@			//函数名称")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@brief ")
	ln=ln+1
	InsBufLine(hbuf,ln,"* ")
	ln=ln+1
	InsBufLine(hbuf,ln,"* ")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@Para[in] : 				//参数输入")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@Para[out] : 				//参数输出")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@return :					//返回值 ")
	ln=ln+1
	InsBufLine(hbuf,ln,"*\@note :						//注解")
	ln=ln+1
	InsBufLine(hbuf,ln,"*********************************************************************************/")
	ln=ln+1

	Savebuf(hbuf)
}

macro Changetolower()
{
	hbuf=GetCurrentBuf()
	context=GetBufSelText(hbuf)
	context=tolower(context)

	SetBufSelText(hbuf,"@context@")

}
