<iREM -- Create Field Array -- >
<iSET fcount=0>
<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT * FROM _Fields WHERE Parent = :DB ;" ALIAS="LoadDB"><iSQLFETCH ALIAS="LoadDB">
  <iWHILE NOTALIAS=i_sqlempty>
    <iSET fcount=<iMATH A=:fcount B=1 O=+>>
    <iEQ NAME="FName_:fcount" VALUE="z:LoadDB_FName" EVAL=TRUE>
    <iEQ NAME="FType_:fcount" VALUE=":LoadDB_FType" EVAL=TRUE>
    <iEQ NAME="FPre_:fcount" VALUE=":LoadDB_FPre" EVAL=TRUE>
    <iEQ NAME="FPost_:fcount" VALUE=":LoadDB_FPost" EVAL=TRUE>
    <iEQ NAME="FSize_:fcount" VALUE=":LoadDB_FSize" EVAL=TRUE>
    <iSQLFETCH ALIAS="LoadDB">
  </iWHILE ALIAS=i_sqlempty>
</iSQL ALIAS="LoadDB">

<iREM -- Setup List for Field Display Order & Count -- >
<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT FieldDisplayOrder FROM _DBs WHERE ID = :DB ;" OUTPUT=":1" NOOUTPUT="0" OUTVAR="FieldDisplayOrder">
<iLISTCREATE NAME="FieldOrder" DELIM="" SRC="FieldDisplayOrder" TYPE=VARIABLE>
<iLISTGET NAME="FieldOrder" OP="COUNT" OUTVAR="FDOCount">

<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="DoConfig"> ALIAS="DoConfig">

  <iIF COND=<iSTRCMP SRC=":Active" DST="on"> ALIAS="YN"><iSET Active=1><iELSE ALIAS="YN"><iSET Active=0></iIF ALIAS="YN">
  <iIF COND=<iSTRCMP SRC=":Delete" DST="on"> ALIAS="YN"><iSET Delete=1><iELSE ALIAS="YN"><iSET Delete=0></iIF ALIAS="YN">

  <iIF EXPR=':Delete' ALIAS="Remove">
    <iHTML DBNAME=':dsn' SQL='DELETE FROM :DBName WHERE ID = :ID ;' NOOUTPUT="Item deleted." FAILURE=":i_sqlerrortext" OUTVAR="msg">
    <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">
  <iELSE ALIAS="Remove">

    <iREM -- Image Handler -- >
    <iSWITCH ALIAS="ImgHandle">
    <iCASE ALIAS="ImgHandle" VALUE="Leave">
      <iSET OrigFile=":CurrentImg">
    </iCASE ALIAS="ImgHandle">
    <iCASE ALIAS="ImgHandle" VALUE="Delete">
      <iIF COND=<iFILE NAME=":imagedir\bbsmanager\:CurrentImg" OP=EXISTS> ALIAS="FileExists">
        <iFILE NAME=":imagedir\bbsmanager\:CurrentImg" OP=DELETE>
        <iSET fumsg="Image removed.">
      </iIF ALIAS="FileExists">
      <iSET OrigFile="">
    </iCASE ALIAS="ImgHandle">
    <iCASE ALIAS="ImgHandle" VALUE=DEFAULT>
      <iREM -- Check for Image Path Existence & Uploaded File -- >
      <iIF COND=<iSTRIN SRC=":i_priv_post" DST="Content-Type:"> ALIAS="IsFile">
        <iEQ NAME='OrigFile' VALUE='<iSTRREV SRC='<iSTRLEFT SRC='<iSTRREV SRC='<iGETMIMENAME>'>' NUM=<iMATH A=<iSTRIN SRC='<iSTRREV SRC='<iGETMIMENAME>'>' DST="\"> B=1 O=->>'>'>
        <iIF NOTCOND=<iSTRCMP SRC=":OrigFile" DST=""> ALIAS="NotBlank">
          <iIF EXPR='NOT <iDIR PATH=":imagedir\bbsmanager" FIRST=TRUE OP=EXISTS>' ALIAS="MakeDir"><iDIR PATH=":imagedir\bbsmanager" FIRST=TRUE OP=MAKE></iIF ALIAS="MakeDir">
          <iINCLUDE NAME="w:\bbsmanager\admin_fileuploader.inc">
        </iIF ALIAS="NotBlank">
      </iIF ALIAS="IsFile">
      <iIF NOTCOND=<iSTRCMP SRC=":fumsg" DST="Image uploaded successfully."> ALIAS="UpFail">
        <iIF COND=<iSTRCMP SRC=":ImgHandle" DST="Replace"> ALIAS="NoRep">
          <iSET fumsg="No replacement uploaded." OrigFile=":CurrentImg">
        <iELSE ALIAS="NoRep">
          <iSET OrigFile="">
        </iIF ALIAS="NoRep">
      <iELSE ALIAS="UpFail">
        <iIF COND=<iISDEF VAR="CurrentImg"> ALIAS="IsCurImg">
          <iIF COND=<iFILE NAME=":imagedir\bbsmanager\:CurrentImg" OP=EXISTS> ALIAS="FileExists"><iFILE NAME=":imagedir\bbsmanager\:CurrentImg" OP=DELETE></iIF ALIAS="FileExists">
        </iIF ALIAS="IsCurImg">
      </iIF ALIAS="UpFail">
    </iCASE ALIAS="ImgHandle">
    </iSWITCH ALIAS="ImgHandle">

    <iIF COND=<iSTRCMP SRC=":ID" DST="NEW"> ALIAS="Insert">
      <iSET sqlstring="INSERT INTO :DBName (Posted, Active">
      <iLOOP INITIAL=1 FINAL=":FDOCount"><iSET sqlstring=`:sqlstring, <iEQ VALUE=":sF_:i_loop" EVAL=TRUE>`></iLOOP>
      <iSET sqlstring=`:sqlstring) VALUES (':Posted', :Active`>
      <iLOOP INITIAL=1 FINAL=":FDOCount">
        <iREM -- Escape Single Quotes for Insert -- >
        <iEQ NAME="insertme" VALUE=":sV_:i_loop" EVAL=TRUE><iREPLACE VAR="insertme" SRC="'" DST="''">
        <iREM -- File Handler -- >
        <iIF EXPR='<iISDEF VAR="OrigFile"> AND NOT <iSTRCMP SRC=":OrigFile" DST=""> AND <iSTRCMP SRC=":insertme" DST="">' ALIAS="IsFile"><iSET insertme=":OrigFile"></IIF ALIAS="IsFile">
        <iSET sqlstring=`:sqlstring, ':insertme'`>
      </iLOOP>
      <iSET sqlstring=`:sqlstring) ;` z="New item added.">
    <iELSE ALIAS="Insert">
      <iSET sqlstring="UPDATE :DBName SET Posted = ':Posted', Active = :Active">
      <iLOOP INITIAL=1 FINAL=":FDOCount">
        <iREM -- Escape Single Quotes for Update -- >
        <iEQ NAME="insertme" VALUE=":sV_:i_loop" EVAL=TRUE><iREPLACE VAR="insertme" SRC="'" DST="''">
        <iREM -- File Handler -- >
        <iIF EXPR='<iISDEF VAR="OrigFile"> AND NOT <iSTRCMP SRC=":OrigFile" DST=""> AND <iSTRCMP SRC=":insertme" DST="">' ALIAS="IsFile"><iSET insertme=":OrigFile"></IIF ALIAS="IsFile">
        <iSET sqlstring=`:sqlstring, <iEQ VALUE=":sF_:i_loop" EVAL=TRUE> = ':insertme'`>
      </iLOOP>
      <iSET sqlstring=`:sqlstring WHERE ID = :ID ;` z="Item updated.">
    </iIF ALIAS="Insert">

    <iHTML DBNAME=':dsn' SQL=`:sqlstring` ESC=FALSE NOOUTPUT="Success" FAILURE=":i_sqlerrortext" OUTVAR="msg">
    <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">
    <iIF COND=<iSTRCMP SRC=":msg" DST="Success"> ALIAS="SetMsg"><iSET msg=":z"></iIF ALIAS="SetMsg">
    <iIF EXPR='<iISDEF VAR="fumsg"> AND NOT <iSTRCMP SRC=":fumsg" DST="">' ALIAS="SetMsg"><iSET msg=":z :fumsg"></iIF ALIAS="SetMsg">

    <iREM iSQLROW DBNAME=':dsn' VARS=':FieldList' QUALIFIER='ID = :ID' TABLE=':DBName'>
  </iIF ALIAS="Remove">

</iIF ALIAS="DoConfig">

<iREM -- Show Status Message -- >
<iIF COND=<iISDEF VAR="msg"> ALIAS="ShowMsg"><CENTER><FONT COLOR="#FF5500" SIZE="+1">:msg</FONT></CENTER><BR></iIF ALIAS="ShowMsg">

<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=4><TR><TD><CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>

<iSET DemoDSN="adminware_copymanager" demo=0 Show=':DBName' ShowAll=1>
<iIF COND=<iSTRCMP SRC=":dsn" DST=":DemoDSN"> ALIAS="IsDemo"><iSET demo=1></iIF ALIAS="IsDemo">
<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT COUNT (*) FROM :Show ;" OUTPUT=":1" NOOUTPUT="0" OUTVAR="bbs_entries">

<iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT * FROM _DBs WHERE ID = :DB ;" ALIAS="LoadDB"><iSQLFETCH ALIAS="LoadDB">

  <iSET dtfmt=":LoadDB_DateFormat"><iIF EXPR=':LoadDB_ShowTime' ALIAS="ShowTime"><iSET dtfmt=":LoadDB_DateFormat :LoadDB_TimeFormat"></iIF ALIAS="ShowTime">
  <iSET DispOrder=";"><iIF EXPR=':LoadDB_Descending' ALIAS="Descending"><iSET DispOrder="DESC ;"></iIF ALIAS="Descending">

  <iSET PMCount=0 WhichRow=1>

  <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT * FROM :Show ORDER BY Posted :DispOrder" ALIAS="GetItems">

  <iSQLFETCH ALIAS="GetItems">

<iREM -- IT DIES HERE! -->

  <iWHILE NOTALIAS="i_sqlempty">
    <iSET PMCount=<iMATH A=:PMCount B=1 O="+">>
    <iSET PMDate=<iCRDATE ODBC=':GetItems_Posted' FMT='%m/%d/%Y'>>

    <iREM -- Define Row Colors -- >
    <iIF EXPR=':WhichRow = 1' ALIAS="WhichColor">
      <iSET RowColor="BGCOLOR='#FFFFFF'" WhichRow=2>
    <iELSEIF EXPR=':WhichRow = 2' ALIAS="WhichColor">
      <iSET RowColor="BGCOLOR='#FFFFEE'" WhichRow=1>
    </iIF ALIAS="WhichColor">

    <FORM METHOD=POST ENCTYPE="multipart/form-data" ACTION="admin.ihtml">
    <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="imagedir" VALUE=":imagedir"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
    <INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Content"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="DB" VALUE=":DB"><INPUT TYPE=HIDDEN NAME="ID" VALUE=":GetItems_ID"><INPUT TYPE=HIDDEN NAME="DBName" VALUE=":DBName">

    <iREM -- Output Items in the DB -- >
    <TR :RowColor>
      <TD><B>Item Date</B></TD><TD><INPUT TYPE=TEXT NAME="Posted" SIZE=16 MAXLENGTH=16 VALUE='<iCRDATE ODBC=':GetItems_Posted' FMT=':dtfmt'>'></TD>
      <TD ALIGN=RIGHT><B>Active? &nbsp;</B></TD><TD><iSET State=""><iIF EXPR=':GetItems_Active' ALIAS="YN"><iSET State="CHECKED"></iIF ALIAS="YN"><INPUT TYPE=CHECKBOX NAME="Active" :State></TD>
    </TR>

    <iREM -- Display Fields in Preferred Order -- >
    <iLOOP INITIAL=1 FINAL=":FDOCount" ALIAS="FDO">
      <iLISTGET NAME="FieldOrder" OP=GETAT INDEX=":FDO" OUTVAR="Next">
      <iREM -- Get Field Settings -- >
      <iEQ NAME="NextField" VALUE=":FName_:Next" EVAL=TRUE><iEQ NAME="FieldType" VALUE=":FType_:Next" EVAL=TRUE><iEQ NAME="FieldSize" VALUE=":FSize_:Next" EVAL=TRUE>
      <iREM -- Remove 'z' Prefix for Display Purposes -- >
      <iSTRRIGHT SRC=":NextField" NUM=<iEVAL EXPR='<iSTRLEN SRC=':NextField'> - 1'> OUTVAR="ViewField">
      <INPUT TYPE=HIDDEN NAME="sF_:FDO" VALUE='<iEQ VALUE=':NextField' EVAL=TRUE>'>
      <TR :RowColor>
        <TD VALIGN=TOP><B>:ViewField</B></TD>
        <TD COLSPAN=3>
          <iSWITCH ALIAS="FieldType">
          <iCASE ALIAS="FieldType" VALUE="Image">
            <iEQ NAME="CurImg" VALUE=':GetItems_:NextField' EVAL=TRUE>
            <INPUT TYPE=FILE NAME='sV_:FDO' SIZE="50" MAXLENGTH="50"><BR>
            <iIF NOTCOND=<iSTRCMP SRC=":CurImg" DST=""> ALIAS="HasImg">
              <iSET ImgURL=":imagedir"><iREPLACE VAR="ImgURL" SRC="d:\" DST="http://www."><iREPLACE VAR="ImgURL" SRC="htdocs\" DST=""><iREPLACE VAR="ImgURL" SRC="\" DST="/">
              [currently <A HREF=":ImgURL/bbsmanager/:CurImg" TARGET="_blank">:CurImg</A>] <INPUT TYPE=HIDDEN NAME="CurrentImg" VALUE=":CurImg"><SELECT NAME="ImgHandle"><OPTION>Leave</OPTION><OPTION>Replace</OPTION><OPTION>Delete</OPTION></SELECT>
            </iIF ALIAS="HasImg">
          </iCASE ALIAS="FieldType">
          <iCASE ALIAS="FieldType" VALUE=DEFAULT>
            <iIF EXPR=':FieldSize GT 50' ALIAS="FieldSizer">
              <iEVAL EXPR=':FieldSize / 51' OUTVAR="InputRows">
              <TEXTAREA NAME='sV_:FDO' WRAP=SOFT ROWS=:InputRows COLS=51><iEQ VALUE=':GetItems_:NextField' EVAL=TRUE></TEXTAREA>
            <iELSEIF EXPR=':FieldSize = 0' ALIAS="FieldSizer">
              <TEXTAREA NAME='sV_:FDO' WRAP=SOFT ROWS=5 COLS=51><iEQ VALUE=':GetItems_:NextField' EVAL=TRUE></TEXTAREA>
            <iELSE ALIAS="FieldSizer">
              <INPUT TYPE=TEXT NAME='sV_:FDO' SIZE=':FieldSize' MAXLENGTH=':FieldSize' VALUE='<iEQ VALUE=':GetItems_:NextField' EVAL=TRUE>'>
            </iIF ALIAS="FieldSizer">
          </iCASE ALIAS="FieldType">
          </iSWITCH ALIAS="FieldType">
        </TD>
      </TR>
    </iLOOP ALIAS="FDO">

    <TR><TD COLSPAN=4 ALIGN=CENTER><B>Delete? &nbsp;</B><INPUT TYPE=CHECKBOX NAME="Delete"> <INPUT TYPE=SUBMIT NAME="DoConfig" VALUE="Update Item"> <INPUT TYPE=RESET VALUE="Undo Changes"><HR NOSHADE></TD></TR>
    </FORM>

    <iSQLFETCH ALIAS="GetItems">
  </iWHILE ALIAS="i_sqlempty">
  </iSQL ALIAS="GetItems">

  <iIF EXPR=':PMCount = 0' ALIAS="NoItems">
    <TR><TD ALIGN=CENTER COLSPAN=4><BR><BLOCKQUOTE><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor">There are no active items in the <B>:Show Database</B> at this time.</FONT></BLOCKQUOTE></TD></TR>
  </iIF ALIAS="NoItems">

<iREM -- Add New Item Code -- >

  <iREM -- Define Row Colors -- >
  <iSET RowColor="BGCOLOR='#FFFFEE'"><iIF EXPR=':WhichRow = 1' ALIAS="WhichColor"><iSET RowColor="BGCOLOR='#FFFFFF'"></iIF ALIAS="WhichColor">

  <FORM METHOD=POST ENCTYPE="multipart/form-data" ACTION="admin.ihtml">
  <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="imagedir" VALUE=":imagedir"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
  <INPUT TYPE=HIDDEN NAME="go" VALUE="Manage Content"><INPUT TYPE=HIDDEN NAME="Config" VALUE=":Config"><INPUT TYPE=HIDDEN NAME="DB" VALUE=":DB"><INPUT TYPE=HIDDEN NAME="ID" VALUE="NEW"><INPUT TYPE=HIDDEN NAME="DBName" VALUE=":DBName">

  <TR><TD COLSPAN=4 ALIGN=CENTER><FONT COLOR="#FF5500" SIZE="+1">Fill out this form to add a new item to the database.</FONT></TD></TR>
  <TR><TD COLSPAN=4>&nbsp;</TD></TR>

  <TR :RowColor>
    <TD><B>Item Date</B></TD><TD><INPUT TYPE=TEXT NAME="Posted" SIZE=16 MAXLENGTH=16 VALUE='<iDATETIME FMT=':dtfmt'>'></TD>
    <TD><B>Active?</B></TD><TD><INPUT TYPE=CHECKBOX NAME="Active" CHECKED></TD>
  </TR>

  <iREM -- Display Fields in Preferred Order -- >
  <iLOOP INITIAL=1 FINAL=":FDOCount" ALIAS="FDO">
    <iLISTGET NAME="FieldOrder" OP=GETAT INDEX=":FDO" OUTVAR="Next">
    <iREM -- Get Field Settings -- >
    <iEQ NAME="NextField" VALUE=":FName_:Next" EVAL=TRUE><iEQ NAME="FieldType" VALUE=":FType_:Next" EVAL=TRUE><iEQ NAME="FieldSize" VALUE=":FSize_:Next" EVAL=TRUE>
    <iREM -- Remove 'z' Prefix for Display Purposes -- >
    <iSTRRIGHT SRC=":NextField" NUM=<iEVAL EXPR='<iSTRLEN SRC=':NextField'> - 1'> OUTVAR="ViewField">
    <INPUT TYPE=HIDDEN NAME="sF_:FDO" VALUE='<iEQ VALUE=':NextField' EVAL=TRUE>'>
    <TR :RowColor>
      <TD VALIGN=TOP><B>:ViewField</B></TD>
      <TD COLSPAN=3>
          <iSWITCH ALIAS="FieldType">
          <iCASE ALIAS="FieldType" VALUE="Image">
            <INPUT TYPE=FILE NAME='sV_:FDO' SIZE="50" MAXLENGTH="50"><BR>
          </iCASE ALIAS="FieldType">
          <iCASE ALIAS="FieldType" VALUE=DEFAULT>
            <iIF EXPR=':FieldSize GT 50' ALIAS="FieldSizer">
              <iEVAL EXPR=':FieldSize / 51' OUTVAR="InputRows">
              <TEXTAREA NAME='sV_:FDO' WRAP=SOFT ROWS=:InputRows COLS=51></TEXTAREA>
            <iELSEIF EXPR=':FieldSize = 0' ALIAS="FieldSizer">
              <TEXTAREA NAME='sV_:FDO' WRAP=SOFT ROWS=5 COLS=51></TEXTAREA>
            <iELSE ALIAS="FieldSizer">
              <INPUT TYPE=TEXT NAME='sV_:FDO' SIZE=':FieldSize' MAXLENGTH=':FieldSize' VALUE="">
            </iIF ALIAS="FieldSizer">
          </iCASE ALIAS="FieldType">
          </iSWITCH ALIAS="FieldType">
      </TD>
    </TR>
  </iLOOP ALIAS="FDO">

  <TR><TD COLSPAN=4 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="DoConfig" VALUE="Add Item"> <INPUT TYPE=RESET VALUE="Undo Changes"><HR NOSHADE></TD></TR>
  </FORM>

<iREM -- Add New Item Code -- >

</iSQL ALIAS="LoadDB">

<FORM METHOD=POST ACTION="admin.ihtml"><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="imagedir" VALUE=":imagedir"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="msg" VALUE="">
<TR><TD COLSPAN=4 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="Back" VALUE="Go Back"></TD></TR>
</FORM>

</TABLE></CENTER></TD></TR></TABLE>

<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT Active FROM _DBs WHERE ID = :DB;" OUTPUT=":1" NOOUTPUT="NA" FAILURE="NA" OUTVAR="Active">
<iHTML LOGIN=":LOGIN" DBNAME=":dsn" SQL="SELECT LiveURL FROM _DBs WHERE ID = :DB;" OUTPUT=":1" NOOUTPUT="NA" FAILURE="NA" OUTVAR="LiveURL">
<iIF EXPR=':Active AND NOT <iSTRCMP SRC=":LiveURL" DST="NA"> AND <iSTRIN SRC=":LiveURL" DST="http://">' ALIAS="GoLive">  <BR><CENTER><A HREF=':LiveURL'>View Live</A></CENTER></iIF ALIAS="GoLive">
