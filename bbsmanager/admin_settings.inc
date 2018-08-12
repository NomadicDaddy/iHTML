<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="DoConfig"> ALIAS="DoConfig">

  <iIF COND=<iSTRCMP SRC=":Active" DST="on"> ALIAS="YN"><iSET Active=1><iELSE ALIAS="YN"><iSET Active=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":ShowDate" DST="on"> ALIAS="YN"><iSET ShowDate=1><iELSE ALIAS="YN"><iSET ShowDate=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":ShowTime" DST="on"> ALIAS="YN"><iSET ShowTime=1><iELSE ALIAS="YN"><iSET ShowTime=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":AltRowColor" DST="on"> ALIAS="YN"><iSET AltRowColor=1><iELSE ALIAS="YN"><iSET AltRowColor=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":RowColor1" DST="">><iSET RowColor1="#FFFFFF"></iIF>
  <iIF COND=<iSTRCMP SRC=":RowColor2" DST="">><iSET RowColor2="#FFFFFF"></iIF>
  <iIF COND=<iSTRCMP SRC=":ArchiveCutoff" DST="">><iSET ArchiveCutoff=21></iIF>
  <iIF COND=<iSTRCMP SRC=":HideHeader" DST="on"> ALIAS="YN"><iSET HideHeader=1><iELSE ALIAS="YN"><iSET HideHeader=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":SortField" DST="">><iSET SortField=0></iIF>
  <iIF COND=<iSTRCMP SRC=":Descending" DST="on"> ALIAS="YN"><iSET Descending=1><iELSE ALIAS="YN"><iSET Descending=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":GroupField" DST="">><iSET GroupField=0></iIF>
  <iIF COND=<iSTRCMP SRC=":ShowHeaderRow" DST="on"> ALIAS="YN"><iSET ShowHeaderRow=1><iELSE ALIAS="YN"><iSET ShowHeaderRow=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":ShowTitles" DST="on"> ALIAS="YN"><iSET ShowTitles=1><iELSE ALIAS="YN"><iSET ShowTitles=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":LinkToField" DST="">><iSET LinkToField=0></iIF>
  <iSET MgrToAddress="pbeazley@onvix.com" MgrFromAddress="bbsmanager@adminware.com">

  <iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="UPDATE _DBs SET Active = :Active, DisplayName = ':DisplayName', LiveURL = ':LiveURL', DateFormat = ':DateFormat', TimeFormat = ':TimeFormat', ShowDate = :ShowDate, ShowTime = :ShowTime, BarColor = ':BarColor', BarTextFace = ':BarTextFace', BarTextSize = ':BarTextSize', BarTextColor = ':BarTextColor', HeadTextFace = ':HeadTextFace', HeadTextSize = ':HeadTextSize', HeadTextColor = ':HeadTextColor', BodyTextFace = ':BodyTextFace', BodyTextSize = ':BodyTextSize', BodyTextColor = ':BodyTextColor', ListTextFace = ':ListTextFace', ListTextSize = ':ListTextSize', ListTextColor = ':ListTextColor', NewIndicator = ':NewIndicator', AltRowColor = :AltRowColor, RowColor1 = ':RowColor1', RowColor2 = ':RowColor2', RPre = ':RPre', RPost = ':RPost', MgrToAddress = ':MgrToAddress', MgrFromAddress = ':MgrFromAddress', ArchiveCutoff = :ArchiveCutoff, HideHeader = :HideHeader, SortField = :SortField, Descending = :Descending, GroupField = :GroupField, ShowHeaderRow = :ShowHeaderRow, ShowTitles = :ShowTitles, FieldDisplayType = :FieldDisplayType, FieldDisplayOrder = ':FieldDisplayOrder', LinkToField = :LinkToField, LinkToText = ':LinkToText' WHERE ID = :DB ;" NOOUTPUT="Database settings saved." FAILURE=":i_sqlerrortext" OUTVAR="msg">
  <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">

  <iREMBLOCK>
  :Active, ':DisplayName', ':LiveURL', ':DateFormat', ':TimeFormat', :ShowDate, :ShowTime, ':BarColor', ':BarTextFace', ':BarTextSize', ':BarTextColor', ':HeadTextFace', ':HeadTextSize', ':HeadTextColor', ':BodyTextFace', ':BodyTextSize', ':BodyTextColor', ':ListTextFace', ':ListTextSize', ':ListTextColor', ':NewIndicator', :AltRowColor, ':RowColor1', ':RowColor2', ':RPre', ':RPost', ':MgrToAddress', ':MgrFromAddress', :ArchiveCutoff, :HideHeader, :SortField, :Descending, :GroupField, :ShowHeaderRow, :ShowTitles, :FieldDisplayType, ':FieldDisplayOrder', :LinkToField, ':LinkToText'
  Active, DisplayName, LiveURL, DateFormat, TimeFormat, ShowDate, ShowTime, BarColor, BarTextFace, BarTextSize, BarTextColor, HeadTextFace, HeadTextSize, HeadTextColor, BodyTextFace, BodyTextSize, BodyTextColor, ListTextFace, ListTextSize, ListTextColor, NewIndicator, AltRowColor, RowColor1, RowColor2, RPre, RPost, MgrToAddress, MgrFromAddress, ArchiveCutoff, HideHeader, SortField, Descending, GroupField, ShowHeaderRow, ShowTitles, FieldDisplayType, FieldDisplayOrder, LinkToField, LinkToText
  </iREMBLOCK>

</iIF ALIAS="DoConfig">

<iREM -- Show Status Message -- >
<iIF COND=<iISDEF VAR="msg"> ALIAS="ShowMsg"><CENTER><FONT COLOR="#FF5500" SIZE="+1">:msg</FONT></CENTER><BR></iIF ALIAS="ShowMsg">

<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=4><TR><TD><CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>

<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT * FROM _DBs WHERE ID = :DB ;" ALIAS="LoadDB"><iSQLFETCH ALIAS="LoadDB">

<iREMBLOCK>
  <FORM NAME="schemePicker">
  <TR><TD>Load Scheme</TD><TD COLSPAN=3><FONT FACE="Arial, Helvetica" SIZE="-1"><SELECT NAME="schemePick" onChange="ChangeScheme(this)"><OPTION VALUE="0"></OPTION>
  <SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript"><!--
  schemeList();
  //--></SCRIPT>
  </SELECT></FONT></TD><TD COLSPAN=2>&nbsp;</TD></TR>
  </FORM>
  <TR><TD COLSPAN=7>&nbsp;</TD></TR>
</iREMBLOCK>

<iREMBLOCK>
 onsubmit="return CheckDupes()"
</iREMBLOCK>

  <FORM NAME="dbsettings" METHOD=POST ACTION="admin.ihtml">
  <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="imagedir" VALUE=":imagedir"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
  <INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Settings"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="DB" VALUE=":DB">

  <TR><TD>Display Name</TD><TD COLSPAN=5><INPUT TYPE=TEXT SIZE=50 MAXLENGTH=50 NAME="DisplayName" VALUE=":LoadDB_DisplayName"></TD>
      <TD COLSPAN=3 ALIGN=RIGHT>Archive Cutoff</TD><TD NOWRAP ALIGN=CENTER><INPUT TYPE=TEXT SIZE=2 MAXLENGTH=2 NAME="ArchiveCutoff" VALUE=":LoadDB_ArchiveCutoff"> days</TD></TR>

  <TR><TD>Live URL</TD><TD COLSPAN=5><INPUT TYPE=TEXT SIZE=50 MAXLENGTH=255 NAME="LiveURL" VALUE=":LoadDB_LiveURL"></TD>
      <TD COLSPAN=3 ALIGN=RIGHT>Active?</TD><TD ALIGN=CENTER><iSET State=""><iIF EXPR=':LoadDB_Active' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="Active" :State></TD></TR>

  <TR><TD>Date Format</TD><TD COLSPAN=2><INPUT TYPE=TEXT SIZE=10 MAXLENGTH=10 NAME="DateFormat" VALUE=":LoadDB_DateFormat"></TD><TD ALIGN=RIGHT>Show?</TD><TD><iSET State=""><iIF EXPR=':LoadDB_ShowDate' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="ShowDate" :State></TD>
      <TD>Time Format</TD><TD><INPUT TYPE=TEXT SIZE=10 MAXLENGTH=10 NAME="TimeFormat" VALUE=":LoadDB_TimeFormat"></TD><TD>Show?</TD><TD><iSET State=""><iIF EXPR=':LoadDB_ShowTime' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="ShowTime" :State></TD>
      <TD ALIGN=CENTER><iDATE FMT=':LoadDB_DateFormat'> <iTIME FMT=':LoadDB_TimeFormat'></TD></TR>

  <TR><TD>Bar Color</TD><TD><INPUT TYPE=TEXT SIZE=7 MAXLENGTH=7 NAME="BarColor" VALUE=":LoadDB_BarColor"></TD><TD WIDTH=23><A HREF="javascript:void(0)" onClick="selectC(1,event.x,event.y)"><IMG SRC="/images/adminware/palette.gif" ALT="Choose Color" WIDTH=23 HEIGHT=22 BORDER=0></A></TD><TD COLSPAN=7 BGCOLOR=":LoadDB_BarColor">&nbsp;</TD></TR>

  <TR><TD ROWSPAN=2>Bar Text</TD><TD ALIGN=CENTER>Font Face</TD><TD COLSPAN=4><INPUT TYPE=TEXT SIZE=25 MAXLENGTH=25 NAME="BarTextFace" VALUE=":LoadDB_BarTextFace"></TD><TD ROWSPAN=2 COLSPAN=4 BGCOLOR=":LoadDB_BarColor" ALIGN=CENTER><FONT FACE=":LoadDB_BarTextFace" SIZE=":LoadDB_BarTextSize" COLOR=":LoadDB_BarTextColor">Example</FONT></TD></TR>
  <TR><TD ALIGN=CENTER>Font Size</TD><TD ALIGN=CENTER><INPUT TYPE=TEXT SIZE=2 MAXLENGTH=2 NAME="BarTextSize" VALUE=":LoadDB_BarTextSize"></TD><TD ALIGN=CENTER>Color</TD><TD ALIGN=CENTER><INPUT TYPE=TEXT SIZE=7 MAXLENGTH=7 NAME="BarTextColor" VALUE=":LoadDB_BarTextColor"></TD><TD WIDTH=23><A HREF="javascript:void(0)" onClick="selectC(2,event.x,event.y)"><IMG SRC="/images/adminware/palette.gif" ALT="Choose Color" WIDTH=23 HEIGHT=22 BORDER=0></A></TD></TR>
  <TR><TD ROWSPAN=2>Head Text</TD><TD ALIGN=CENTER>Font Face</TD><TD COLSPAN=4><INPUT TYPE=TEXT SIZE=25 MAXLENGTH=25 NAME="HeadTextFace" VALUE=":LoadDB_HeadTextFace"></TD><TD ROWSPAN=2 COLSPAN=4 ALIGN=CENTER><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor">Example</FONT></TD></TR>
  <TR><TD ALIGN=CENTER>Font Size</TD><TD ALIGN=CENTER><INPUT TYPE=TEXT SIZE=2 MAXLENGTH=2 NAME="HeadTextSize" VALUE=":LoadDB_HeadTextSize"></TD><TD ALIGN=CENTER>Color</TD><TD ALIGN=CENTER><INPUT TYPE=TEXT SIZE=7 MAXLENGTH=7 NAME="HeadTextColor" VALUE=":LoadDB_HeadTextColor"></TD><TD WIDTH=23><A HREF="javascript:void(0)" onClick="selectC(2,event.x,event.y)"><IMG SRC="/images/adminware/palette.gif" ALT="Choose Color" WIDTH=23 HEIGHT=22 BORDER=0></A></TD></TR>
  <TR><TD ROWSPAN=2>Body Text</TD><TD ALIGN=CENTER>Font Face</TD><TD COLSPAN=4><INPUT TYPE=TEXT SIZE=25 MAXLENGTH=25 NAME="BodyTextFace" VALUE=":LoadDB_BodyTextFace"></TD><TD ROWSPAN=2 COLSPAN=4 ALIGN=CENTER><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Example</FONT></TD></TR>
  <TR><TD ALIGN=CENTER>Font Size</TD><TD ALIGN=CENTER><INPUT TYPE=TEXT SIZE=2 MAXLENGTH=2 NAME="BodyTextSize" VALUE=":LoadDB_BodyTextSize"></TD><TD ALIGN=CENTER>Color</TD><TD ALIGN=CENTER><INPUT TYPE=TEXT SIZE=7 MAXLENGTH=7 NAME="BodyTextColor" VALUE=":LoadDB_BodyTextColor"></TD><TD WIDTH=23><A HREF="javascript:void(0)" onClick="selectC(2,event.x,event.y)"><IMG SRC="/images/adminware/palette.gif" ALT="Choose Color" WIDTH=23 HEIGHT=22 BORDER=0></A></TD></TR>
  <TR><TD ROWSPAN=2>List Text</TD><TD ALIGN=CENTER>Font Face</TD><TD COLSPAN=4><INPUT TYPE=TEXT SIZE=25 MAXLENGTH=25 NAME="ListTextFace" VALUE=":LoadDB_ListTextFace"></TD><TD ROWSPAN=2 COLSPAN=4 ALIGN=CENTER><FONT FACE=":LoadDB_ListTextFace" SIZE=":LoadDB_ListTextSize" COLOR=":LoadDB_ListTextColor">Example</FONT></TD></TR>
  <TR><TD ALIGN=CENTER>Font Size</TD><TD ALIGN=CENTER><INPUT TYPE=TEXT SIZE=2 MAXLENGTH=2 NAME="ListTextSize" VALUE=":LoadDB_ListTextSize"></TD><TD ALIGN=CENTER>Color</TD><TD ALIGN=CENTER><INPUT TYPE=TEXT SIZE=7 MAXLENGTH=7 NAME="ListTextColor" VALUE=":LoadDB_ListTextColor"></TD><TD WIDTH=23><A HREF="javascript:void(0)" onClick="selectC(2,event.x,event.y)"><IMG SRC="/images/adminware/palette.gif" ALT="Choose Color" WIDTH=23 HEIGHT=22 BORDER=0></A></TD></TR>

  <TR><TD>New Indicator</TD><TD COLSPAN=5><INPUT TYPE=TEXT SIZE=50 MAXLENGTH=255 NAME="NewIndicator" VALUE=":LoadDB_NewIndicator"></TD><TD COLSPAN=4 ALIGN=CENTER>:LoadDB_NewIndicator</TD></TR>

  <TR><TD NOWRAP>Row Color #1</TD><TD><INPUT TYPE=TEXT SIZE=7 MAXLENGTH=7 NAME="RowColor1" VALUE=":LoadDB_RowColor1"></TD><TD WIDTH=23><A HREF="javascript:void(0)" onClick="selectC(6,event.x,event.y)"><IMG SRC="/images/adminware/palette.gif" ALT="Choose Color" WIDTH=23 HEIGHT=22 BORDER=0></A></TD><TD ROWSPAN=2 COLSPAN=2 ALIGN=RIGHT>Alternate Colors?</TD><TD ROWSPAN=2><iSET State=""><iIF EXPR=':LoadDB_AltRowColor' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="AltRowColor" :State></TD>
      <TD COLSPAN=4 BGCOLOR=":LoadDB_RowColor1" ALIGN=CENTER><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Example</FONT></TD></TR>
  <TR><TD NOWRAP>Row Color #2</TD><TD><INPUT TYPE=TEXT SIZE=7 MAXLENGTH=7 NAME="RowColor2" VALUE=":LoadDB_RowColor2"></TD><TD WIDTH=23><A HREF="javascript:void(0)" onClick="selectC(7,event.x,event.y)"><IMG SRC="/images/adminware/palette.gif" ALT="Choose Color" WIDTH=23 HEIGHT=22 BORDER=0></A></TD><TD COLSPAN=4 BGCOLOR=":LoadDB_RowColor2" ALIGN=CENTER><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Example</FONT></TD>

  <TR><TD NOWRAP>Row Pre-Text</TD><TD COLSPAN=4><INPUT TYPE=TEXT SIZE=30 MAXLENGTH=50 NAME="RPre" VALUE=":LoadDB_RPre"></TD>
      <TD NOWRAP>Row Post-Text</TD><TD COLSPAN=4><INPUT TYPE=TEXT SIZE=30 MAXLENGTH=50 NAME="RPost" VALUE=":LoadDB_RPost"></TD></TR>

  <TR><TD>Hide Header?</TD><TD><iSET State=""><iIF EXPR=':LoadDB_HideHeader' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="HideHeader" :State></TD><TD>&nbsp;</TD>
      <TD NOWRAP>Show Header Row?</TD><TD><iSET State=""><iIF EXPR=':LoadDB_ShowHeaderRow' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="ShowHeaderRow" :State></TD>
      <TD>Show Titles?</TD><TD><iSET State=""><iIF EXPR=':LoadDB_ShowTitles' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="ShowTitles" :State></TD><TD>&nbsp;</TD><TD>&nbsp;</TD><TD>&nbsp;</TD></TR>

  <TR><TD NOWRAP>Group By Field</TD><TD COLSPAN=2><SELECT NAME="GroupField">
      <iSET State=""><iIF EXPR=':LoadDB_GroupField = 0' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN"><OPTION VALUE="0" :State>-- None --</OPTION>
      <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT ID,FName FROM _Fields WHERE Parent = :DB ;" ALIAS="LoadFields"><iSQLFETCH ALIAS="LoadFields">
        <iWHILE NOTALIAS=i_sqlempty>
          <iSET State=""><iIF EXPR=':LoadDB_GroupField = :LoadFields_ID' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN">
          <OPTION VALUE=":LoadFields_ID" :State>:LoadFields_FName</OPTION>
          <iSQLFETCH ALIAS="LoadFields">
        </iWHILE ALIAS=i_sqlempty>
      </iSQL ALIAS="LoadFields">
      </SELECT></TD>
      <TD>Descending?</TD><TD><iSET State=""><iIF EXPR=':LoadDB_Descending' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="Descending" :State></TD>
      <TD NOWRAP>Sort By Field</TD><TD><SELECT NAME="SortField">
      <iSET State=""><iIF EXPR=':LoadDB_SortField = 0' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN"><OPTION VALUE="0" :State>-- As Entered --</OPTION>
      <iSET State=""><iIF EXPR=':LoadDB_SortField = -1' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN"><OPTION VALUE="-1" :State>-- Date Posted --</OPTION>
      <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT ID,FName FROM _Fields WHERE Parent = :DB ;" ALIAS="LoadFields"><iSQLFETCH ALIAS="LoadFields">
        <iWHILE NOTALIAS=i_sqlempty>
          <iSET State=""><iIF EXPR=':LoadDB_SortField = :LoadFields_ID' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN">
          <OPTION VALUE=":LoadFields_ID" :State>:LoadFields_FName</OPTION>
          <iSQLFETCH ALIAS="LoadFields">
        </iWHILE ALIAS=i_sqlempty>
      </iSQL ALIAS="LoadFields">
      </SELECT></TD><TD>&nbsp;</TD><TD>&nbsp;</TD><TD>&nbsp;</TD></TR>

  <TR><TD>Field Display</TD><TD COLSPAN=2><SELECT NAME="FieldDisplayType">
      <iSET State=""><iIF EXPR=':LoadDB_FieldDisplayType = 1' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN"><OPTION VALUE="1" :State>Columnar</OPTION>
      <iSET State=""><iIF EXPR=':LoadDB_FieldDisplayType = 0' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN"><OPTION VALUE="0" :State>Cellular</OPTION></SELECT></TD>
      <TD COLSPAN=2>Field Order</TD><TD COLSPAN=5><INPUT TYPE=TEXT SIZE=40 MAXLENGTH=40 NAME="FieldDisplayOrder" VALUE=":LoadDB_FieldDisplayOrder"></TD></TR>

  <TR><TD>LinkTo Field</TD><TD COLSPAN=2><SELECT NAME="LinkToField">
      <iSET State=""><iIF EXPR=':LoadDB_LinkToField = 0' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN">
      <OPTION VALUE="0" :State>-- None --</OPTION>
      <iSET FieldCnt=0>
      <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT FName FROM _Fields WHERE Parent = :DB ;" ALIAS="LoadFields"><iSQLFETCH ALIAS="LoadFields">
        <iWHILE NOTALIAS=i_sqlempty>
          <iSET FieldCnt='<iMATH A=:FieldCnt B=1 O=+>'>
          <iSET State=""><iIF EXPR=':LoadDB_LinkToField = :FieldCnt' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN">
          <OPTION VALUE=":FieldCnt" :State>:LoadFields_FName</OPTION>
          <iSQLFETCH ALIAS="LoadFields">
        </iWHILE ALIAS=i_sqlempty>
      </iSQL ALIAS="LoadFields">
<iREMBLOCK>
      <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT ID,FName FROM _Fields WHERE Parent = :DB ;" ALIAS="LoadFields"><iSQLFETCH ALIAS="LoadFields">
        <iWHILE NOTALIAS=i_sqlempty>
          <iSET State=""><iIF EXPR=':LoadDB_LinkToField = :LoadFields_ID' ALIAS="YN"><iSET State="SELECTED"></iIF ALIAS="YN">
          <OPTION VALUE=":LoadFields_ID" :State>:LoadFields_FName</OPTION>
          <iSQLFETCH ALIAS="LoadFields">
        </iWHILE ALIAS=i_sqlempty>
      </iSQL ALIAS="LoadFields">
</iREMBLOCK>
      </SELECT></TD>
      <TD COLSPAN=2>LinkTo Text</TD><TD COLSPAN=5><INPUT TYPE=TEXT SIZE=40 MAXLENGTH=50 NAME="LinkToText" VALUE=":LoadDB_LinkToText"></TD></TR>

</iSQL ALIAS="LoadDB">

<TR><TD COLSPAN=10>&nbsp;</TD></TR>
<TR><TD COLSPAN=10 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="DoConfig" VALUE="Save Settings"></TD></TR>
</FORM>

<FORM METHOD=POST ACTION="admin.ihtml"><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="imagedir" VALUE=":imagedir"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="msg" VALUE="">
<TR><TD COLSPAN=10 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="Back" VALUE="Go Back"></TD></TR>
</FORM>

<iREMBLOCK>
<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT * FROM _Fields WHERE Parent = :DB ;" ALIAS="LoadFields"><iSQLFETCH ALIAS="LoadFields">
</iSQL ALIAS="LoadFields">
</iREMBLOCK>

</TABLE></CENTER></TD></TR></TABLE><BR>

<iREM -- BBSManager Preview -- >
<CENTER><FONT SIZE="+1"><B><I>Preview</I></B>
<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT Active FROM _DBs WHERE ID = :DB;" OUTPUT=":1" NOOUTPUT="NA" FAILURE="NA" OUTVAR="Active">
<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT LiveURL FROM _DBs WHERE ID = :DB;" OUTPUT=":1" NOOUTPUT="NA" FAILURE="NA" OUTVAR="LiveURL">
<iIF EXPR=':Active AND NOT <iSTRCMP SRC=":LiveURL" DST="NA"> AND <iSTRIN SRC=":LiveURL" DST="http://">' ALIAS="GoLive">  or <B><I><A HREF=':LiveURL'>View Live</A></I></B></iIF ALIAS="GoLive">
</FONT></CENTER><BR>
<iSET dsn=':dsn' Show=':DBName' ShowAll=1 ShowColNums=1><iINCLUDE NAME="w:\bbsmanager\bbsmanager.inc">
