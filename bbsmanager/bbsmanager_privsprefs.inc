<iREM -- Get PrivString -- >
<iIF NOTCOND=<iSTRCMP SRC=":bbs_un" DST="Anonymous"> ALIAS="GetPriv">
  <iIF COND=<iSTRCMP SRC=":LoadDB_AuthType" DST="Numeric">><iSET EID="EID_Numeric" EIDQual=""><iELSE><iSET EID="EID_Text" EIDQual="'"></iIF>
  <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Privs FROM _Members :IfSQL WHERE :EID = :EIDQual:bbs_un:EIDQual ;" ESC=FALSE OUTPUT=":1" NOOUTPUT="z" FAILURE="z" OUTVAR="PrivString">
</iIF ALIAS="GetPriv">

<iREM -- If PrivString Missing or User is Anonymous, Get Default Privs -->
<iIF EXPR='<iSTRCMP SRC=":bbs_un" DST="Anonymous"> OR <iSTRCMP SRC=":PrivString" DST="z">' ALIAS="GetPriv">
  <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Privs FROM _Members :IfSQL WHERE ID = 1 ;" OUTPUT=":1" NOOUTPUT="00000" FAILURE="00000" OUTVAR="PrivString">
</iIF ALIAS="GetPriv">

<iREM -- Get PrefString -- >
<iIF NOTCOND=<iSTRCMP SRC=":bbs_un" DST="Anonymous"> ALIAS="GetPref">
  <iIF COND=<iSTRCMP SRC=":LoadDB_AuthType" DST="Numeric">><iSET EID="EID_Numeric" EIDQual=""><iELSE><iSET EID="EID_Text" EIDQual="'"></iIF>
  <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Prefs FROM _Members :IfSQL WHERE :EID = :EIDQual:bbs_un:EIDQual ;" ESC=FALSE OUTPUT=":1" NOOUTPUT="z" FAILURE="z" OUTVAR="PrefString">
</iIF ALIAS="GetPref">

<iREM -- If PrefString Missing or User is Anonymous, Get Default Prefs -->
<iIF EXPR='<iSTRCMP SRC=":bbs_un" DST="Anonymous"> OR <iSTRCMP SRC=":PrefString" DST="z">' ALIAS="GetPref">
  <iSET DefPref=":LoadDB_DayRange"><iSTRCAT DST="DefPref" SRC="0000">
  <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Prefs FROM _Members :IfSQL WHERE ID = 1 ;" OUTPUT=":1" NOOUTPUT=":DefPref" FAILURE=":DefPref" OUTVAR="PrefString">
</iIF ALIAS="GetPref">

<iREM -- Get Default Age Range -- >
<iIF NOTCOND=<iISDEF VAR="Age"> ALIAS="GetAgePref">
  <iSTRSPAN SRC=":PrefString" FIRST=1 NUM=1 OUTVAR="AgeBit">
  <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Age FROM _Ages :IfSQL WHERE ID = :AgeBit ;" OUTPUT=":1" NOOUTPUT="1" FAILURE="1" OUTVAR="Age">
</iIF ALIAS="GetAgePref">

<iREM -- Get Signature -- >
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Signature FROM _Members :IfSQL WHERE :EID = :EIDQual:bbs_un:EIDQual ;" ESC=FALSE OUTPUT=":1" NOOUTPUT="" FAILURE="" OUTVAR="Signature">

<iREMBLOCK>
<iREM -- Log Privs & Prefs for Testing -- >
<iFILE NAME="d:\luvlink.com\log\privsprefs.log" DATA=`<iDATETIME> | :i_ip | :bbs_un | PrivString = ':PrivString' | PrefString = ':PrefString':i$crlf` OP=APPEND MODE=TEXT>
</iREMBLOCK>
