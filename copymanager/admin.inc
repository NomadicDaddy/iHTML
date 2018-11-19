<iREMBLOCK>
adminware CopyManager (Admin Module)
Copyright � 1998-2002 adminware, llc
</iREMBLOCK>

<iSET AWPAV="CopyManager Admin v1.3.96.1" AWPID="copymanager" AWPD="w:\copymanager">

<iREM -- TEMPORARY!!!! -- >
<iREMBLOCK>
<iDEFAULT NAME="login" VALUE="tampabaymutiny/mtbmf">
</iREMBLOCK>

<iDEFAULT NAME="dsn" VALUE=""><iDEFAULT NAME="login" VALUE="/">
<iIF COND=<iSTRCMP SRC=":dsn" DST="">><iSTOP></iIF>

<iINCLUDE NAME="w:\ifuncs\errorHandler.inc">
<iINCLUDE NAME="w:\shared\config.inc">

<iINCLUDE NAME=":AWPD\admin_banner.inc">

<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="copymanager.js"></SCRIPT>
<CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=3 CELLPADDING=2><TR><TD ALIGN=CENTER><BR>

<iDEFAULT NAME="login" VALUE="/">

<iHTML LOGIN=":login" DBNAME=":dsn" SQL="SELECT ID FROM _Users ;" OUTPUT=":1" NOOUTPUT="0" FAILURE="0" OUTVAR="isDBCheck">

<iIF EXPR=':isDBCheck > 0' ALIAS="IsDB">

  <iIF COND=<iISDEF VAR="LoginSubmit"> ALIAS="LoggingIn">

    <iSQL LOGIN=":login" DBNAME=":dsn" SQL="SELECT Password FROM _Users :IfSQL WHERE UserName=':UserName' ;" ALIAS="LoginCheck"><iSQLFETCH ALIAS="LoginCheck">
      <iIF COND=<iSTRICMP SRC=":Password" DST=":LoginCheck_Password"> ALIAS="LoggedIn">

        <iSET dologin=0>
        <iSWITCH ALIAS="go">
        <iCASE ALIAS="go" VALUE="Change Password"><iINCLUDE NAME=":AWPD\admin_chgpwd.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Add New Content"><iINCLUDE NAME=":AWPD\admin_addcontent.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Manage Existing Content"><iINCLUDE NAME=":AWPD\admin_editcontent.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Manage Settings"><iINCLUDE NAME=":AWPD\admin_settings.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Manage Fields"><iREM INCLUDE NAME=":AWPD\admin_fields.inc"><iSET msg="That option is unavailable at this time." go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="View Live"><iHTML LOGIN=":login" DBNAME=":dsn" SQL="SELECT LiveURL FROM _DBs :IfSQL WHERE ID = :DB;" OUTPUT=":1" NOOUTPUT="NA" FAILURE="NA" OUTVAR="LiveURL"><iIF EXPR='NOT <iSTRCMP SRC=":LiveURL" DST="NA"> AND <iSTRIN SRC=":LiveURL" DST="http://">' ALIAS="GoLive"><iREDIR URL=":LiveURL"></iIF ALIAS="GoLive"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Make Active"><iHTML LOGIN=":login" DBNAME=":dsn" SQL="UPDATE _DBs SET Active = 1 WHERE ID = :DB ;" NOOUTPUT="Database made active." FAILURE=":i_sqlerrortext" OUTVAR="msg"><iSET go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Make Inactive"><iHTML LOGIN=":login" DBNAME=":dsn" SQL="UPDATE _DBs SET Active = 0 WHERE ID = :DB ;" NOOUTPUT="Database made inactive." FAILURE=":i_sqlerrortext" OUTVAR="msg"><iSET go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Delete Database"><iHTML LOGIN=":login" DBNAME=":dsn" SQL="UPDATE _DBs SET Active = 0 WHERE ID = :DB ;" NOOUTPUT="Database made inactive.  Unable to delete." FAILURE=":i_sqlerrortext" OUTVAR="msg"><iSET go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Contact adminware Support"><iINCLUDE NAME=":AWPD\admin_support.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Visit adminware Support"><iREDIR URL="http://adminware.com/support/"></iCASE ALIAS="go">
        <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">

        <iCASE ALIAS="go" VALUE=DEFAULT>

          <iDEFAULT NAME="msg" VALUE="You have logged in successfully.">

          <TABLE WIDTH="100%" BORDER=0 CELLSPACING=3 CELLPADDING=2>

          <TR><TD WIDTH=1% NOWRAP><B><U>ID</U></B></TD><TD>&nbsp; <B><U>Database Name</U></B></TD><TD>&nbsp; <B><U>Current Status</U></B></TD><TD WIDTH=1% NOWRAP><B><U>Management Options</U></B></TD></TR>
          <iSQL LOGIN=":login" DBNAME=":dsn" SQL="SELECT ID,Name,Active,LiveURL FROM _DBs ;" ALIAS="LoadDB"><iSQLFETCH ALIAS="LoadDB">
            <iWHILE NOTALIAS=i_sqlempty>

              <FORM METHOD=POST ACTION="admin.ihtml"><INPUT TYPE=HIDDEN NAME="LoginSubmit"><INPUT TYPE=HIDDEN NAME="login" VALUE=":login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="imagedir" VALUE=":imagedir"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="DB" VALUE=":LoadDB_ID">
              <TR BGCOLOR="#FFFFEE">
                <TD ALIGN=CENTER WIDTH=1% NOWRAP>:LoadDB_ID</TD><TD>&nbsp; <B>:LoadDB_Name</B></TD><TD>&nbsp; <iIF EXPR=':LoadDB_Active' ALIAS="YN"><B>Active</B><iELSE ALIAS="YN">Inactive</iIF ALIAS="YN"></TD>
                <TD WIDTH=1% NOWRAP><SELECT NAME="go" onChange="form.submit()">
                  <OPTION>Add New Content</OPTION><OPTION>Manage Existing Content</OPTION><OPTION>Manage Settings</OPTION><OPTION>Manage Fields</OPTION>
                  <iIF EXPR=':LoadDB_Active' ALIAS="YN">
                    <iIF EXPR='NOT <iSTRCMP SRC=":LoadDB_LiveURL" DST="NA"> AND <iSTRIN SRC=":LoadDB_LiveURL" DST="http://">' ALIAS="GoLive"><OPTION>View Live</OPTION></iIF ALIAS="GoLive">
                    <OPTION>Make Inactive</OPTION>
                  <iELSE ALIAS="YN">
                    <OPTION>Make Active</OPTION>
                  </iIF ALIAS="YN">
                  <OPTION>Delete Database</OPTION></SELECT> <INPUT TYPE=SUBMIT NAME="Config" VALUE="Go!">
                </TD>
              </TR>
              </FORM>

              <iSQLFETCH ALIAS="LoadDB">
            </iWHILE ALIAS=i_sqlempty>
          </iSQL ALIAS="LoadDB">

          <TR><TD COLSPAN=4>&nbsp;</TD></TR>
          <FORM METHOD=POST ACTION="admin.ihtml"><INPUT TYPE=HIDDEN NAME="LoginSubmit"><INPUT TYPE=HIDDEN NAME="login" VALUE=":login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="imagedir" VALUE=":imagedir"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
          <TR><TD COLSPAN=4 ALIGN=CENTER><B>Other Options:</B> <SELECT NAME="go" onChange="form.submit()"><OPTION>Change Password</OPTION><OPTION>Contact adminware Support</OPTION></SELECT> <INPUT TYPE=SUBMIT NAME="Config" VALUE="Go!"></TD></TR>
          </FORM>

          </TABLE>

        </iCASE ALIAS="go">

        </iSWITCH ALIAS="go">

      <iELSE ALIAS="LoggedIn">
        <iSET msg="Your username and/or password is invalid.  Please try again.">
      </iIF ALIAS="LoggedIn">
    </iSQL ALIAS="LoginCheck">

  </iIF ALIAS="LoggingIn">

  <iIF NOTCOND=<iISDEF VAR="dologin"> ALIAS="ShowLogin">

    <iIF NOTCOND=<iISDEF VAR="UserName"> ALIAS="z"><iSET UserName=""></iIF ALIAS="z">

    Enter your username and password to administer your CopyManager.<BR><BR>
    <FORM METHOD=POST ACTION="admin.ihtml"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="login" VALUE=":login"><INPUT TYPE=HIDDEN NAME="imagedir" VALUE=":imagedir">
    <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=5 BGCOLOR="#CFCFCF">
      <TR><TD>UserName:</TD><TD><INPUT TYPE=TEXT NAME="UserName" VALUE=":UserName" SIZE=15></TD></TR>
      <TR><TD>Password:</TD><TD><INPUT TYPE=PASSWORD NAME="Password" SIZE=15></TD></TR>
      <TR><TD COLSPAN=2 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="LoginSubmit" VALUE=" Login "></TD></TR>
    </TABLE></FORM>

  </iIF ALIAS="ShowLogin">

<iELSE ALIAS="IsDB">
  <FONT COLOR="#FF0000"><B>There is no CopyManager Client with that DSN currently setup.</B></FONT><BR>Check the name and try again.
</iIF ALIAS="IsDB">

<BR></TD></TR></TABLE></CENTER>
<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR="#A0B8C8"><TD>&nbsp;<iIF COND=<iISDEF VAR="msg"> ALIAS="ShowMsg"><FONT FACE="Arial,Helvetica" SIZE="2" COLOR="#000066"><B>:msg</B></FONT></iIF ALIAS="ShowMsg"></TD><TD ALIGN=RIGHT><FONT FACE="Arial,Helvetica" SIZE="2" COLOR="#FFFFFF"><B>:AWPAV</B></FONT></TD></TR><TR><TD VALIGN=TOP><FONT FACE="Arial,Helvetica" SIZE="-2"><B>Copyright &copy; 2001-2002 adminware, llc</B></FONT></TD><TD ALIGN=RIGHT VALIGN=TOP><FONT FACE="Arial,Helvetica" SIZE="-2"><B><A HREF="http://adminware.com/" onMouseOver="status='adminware'; return true;" onMouseOut="status='';">http://adminware.com/</A></B></FONT></TD></TR></TABLE>
