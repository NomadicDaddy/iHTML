<iREMBLOCK>
adminware AuthManager v1.2.271.1 Administration Module
Copyright � 2000 adminware, llc
</iREMBLOCK>

<iSET AWPV="AuthManager v1.2.171.1" AWPID="authmanager" AWPD="w:\authmanager">

<iINCLUDE NAME="w:\ifuncs\errorHandler.inc">

<CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=3 CELLPADDING=2><TR><TD ALIGN=CENTER><BR>

<iDEFAULT NAME="am_login" VALUE="/">
<iIF EXPR=<iHTML DBNAME=":dsn" SQL="SELECT ID FROM _Users :IfSQL ;" OUTPUT=":1" FAILURE="0" NOOUTPUT="0"> ALIAS="IsArea">

  <iINCLUDE NAME="w:\shared\config.inc">
  <iINCLUDE NAME=":AWPD\banner.inc">

  <iIF COND=<iISDEF VAR="Login"> ALIAS="LoggingIn">

    <iSQL DBNAME=":dsn" SQL="SELECT Password FROM _Users :IfSQL WHERE UserName=':UserName' ;" ALIAS="LoginCheck"><iSQLFETCH ALIAS="LoginCheck">
      <iIF COND=<iSTRICMP SRC=":Password" DST=":LoginCheck_Password"> ALIAS="LoggedIn">

        <iSET dologin=0>
        <iSWITCH ALIAS="go">
        <iCASE ALIAS="go" VALUE="Manage Existing Users"><iINCLUDE NAME=":AWPD\manage_users.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Add a User"><iINCLUDE NAME=":AWPD\add_user.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Manage Fields"><iREM INCLUDE NAME=":AWPD\manage_fields.inc"><iSET msg="That option is unavailable at this time." go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Enable Protection"><iHTML DBNAME=":dsn" SQL="UPDATE _Areas SET Active = 1 :IfSQL WHERE ID = :Area ;" NOOUTPUT="Area made active." FAILURE=":i_sqlerrortext" OUTVAR="msg"><iSET go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Disable Protection"><iHTML DBNAME=":dsn" SQL="UPDATE _Areas SET Active = 0 :IfSQL WHERE ID = :Area ;" NOOUTPUT="Area made inactive." FAILURE=":i_sqlerrortext" OUTVAR="msg"><iSET go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Make Case Sensitive"><iHTML DBNAME=":dsn" SQL="UPDATE _Areas SET CaseSensitive = 1 :IfSQL WHERE ID = :Area ;" NOOUTPUT="Area made case sensitive." FAILURE=":i_sqlerrortext" OUTVAR="msg"><iSET go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Make Not Case Sensitive"><iHTML DBNAME=":dsn" SQL="UPDATE _Areas SET CaseSensitive = 0 :IfSQL WHERE ID = :Area ;" NOOUTPUT="Area made not case sensitive." FAILURE=":i_sqlerrortext" OUTVAR="msg"><iSET go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Remove Area"><iHTML DBNAME=":dsn" SQL="UPDATE _Areas SET Active = 0 :IfSQL WHERE ID = :Area ;" NOOUTPUT="Area made inactive.  Unable to delete at this time." FAILURE=":i_sqlerrortext" OUTVAR="msg"><iSET go="default"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Add New Area"><iSET msg="That option is unavailable at this time." go="default"></iCASE ALIAS="go">

        <iCASE ALIAS="go" VALUE="Change Password"><iINCLUDE NAME="w:\shared\change_password.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Contact adminware Support"><iINCLUDE NAME="w:\shared\support_request.inc"></iCASE ALIAS="go">
        <iCASE ALIAS="go" VALUE="Visit adminware Support"><iREDIR URL="http://adminware.com/support/"></iCASE ALIAS="go">
        <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">

        <iCASE ALIAS="go" VALUE=DEFAULT>

          <iDEFAULT NAME="msg" VALUE="You have logged in successfully.">

          <TABLE WIDTH="100%" BORDER=0 CELLSPACING=3 CELLPADDING=2>

          <TR><TD NOWRAP>&nbsp; <B><U>Area Name</U></B></TD><TD NOWRAP>&nbsp; <B><U>Secured Location</U></B></TD><TD NOWRAP>&nbsp; <B><U>Current Status</U></B></TD><TD NOWRAP>&nbsp; <B><U>Case Sensitive?</U></B></TD><TD WIDTH=1% NOWRAP><B><U>Management Options</U></B></TD></TR>
          <iSQL DBNAME=":dsn" SQL="SELECT * FROM _Areas :IfSQL ;" ALIAS="LoadDB"><iSQLFETCH ALIAS="LoadDB">
            <iWHILE NOTALIAS=i_sqlempty>

              <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="Area" VALUE=":LoadDB_ID">
              <TR BGCOLOR="#FFFFEE">
                <TD>&nbsp; <B>:LoadDB_Name</B></TD><TD WIDTH=1% NOWRAP>&nbsp; :LoadDB_URL</TD>
                <TD>&nbsp; <iIF EXPR=':LoadDB_Active' ALIAS="YN"><B>Active</B><iELSE ALIAS="YN">Inactive</iIF ALIAS="YN"></TD>
                <TD>&nbsp; <iIF EXPR=':LoadDB_CaseSensitive' ALIAS="YN"><B>Yes</B><iELSE ALIAS="YN">No</iIF ALIAS="YN"></TD>
                <TD WIDTH=1% NOWRAP><SELECT NAME="go" onChange="form.submit()">
                  <OPTION>Manage Existing Users</OPTION><OPTION>Add a User</OPTION><OPTION>Manage Fields</OPTION>
                  <iIF EXPR=':LoadDB_Active' ALIAS="YN"><OPTION>Disable Protection</OPTION><iELSE ALIAS="YN"><OPTION>Enable Protection</OPTION></iIF ALIAS="YN">
                  <iIF EXPR=':LoadDB_CaseSensitive' ALIAS="YN"><OPTION>Make Not Case Sensitive</OPTION><iELSE ALIAS="YN"><OPTION>Make Case Sensitive</OPTION></iIF ALIAS="YN">
                  <OPTION>Remove Area</OPTION></SELECT> <INPUT TYPE=SUBMIT NAME="Config" VALUE="Go!">
                </TD>
              </TR>
              </FORM>

              <iSQLFETCH ALIAS="LoadDB">
            </iWHILE ALIAS=i_sqlempty>
          </iSQL ALIAS="LoadDB">

          <TR><TD COLSPAN=4>&nbsp;</TD></TR>
          <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password">
          <TR><TD COLSPAN=4 ALIGN=CENTER><B>Other Options:</B> <SELECT NAME="go" onChange="form.submit()"><OPTION>Add New Area</OPTION><OPTION>Change Password</OPTION><OPTION>Contact adminware Support</OPTION></SELECT> <INPUT TYPE=SUBMIT NAME="Config" VALUE="Go!"></TD></TR>
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

    Enter your username and password to administer your AuthManager.<BR><BR>
    <FORM METHOD=POST ACTION=:i_script_name><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn">
    <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=5 BGCOLOR="#CFCFCF">
      <TR><TD>UserName:</TD><TD><INPUT TYPE=TEXT NAME="UserName" VALUE=":UserName" SIZE=15></TD></TR>
      <TR><TD>Password:</TD><TD><INPUT TYPE=PASSWORD NAME="Password" SIZE=15></TD></TR>
      <TR><TD COLSPAN=2 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="Login" VALUE=" Login "></TD></TR>
    </TABLE></FORM>

  </iIF ALIAS="ShowLogin">

<iELSE ALIAS="IsArea">
  <FONT COLOR="#FF0000"><B>There is no AuthManager with that DSN currently setup.</B></FONT><BR>Check the name and try again.
</iIF ALIAS="IsArea">

<BR></TD></TR></TABLE></CENTER>
<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR="#A0B8C8"><TD>&nbsp;<iIF COND=<iISDEF VAR="msg"> ALIAS="ShowMsg"><FONT FACE="Arial,Helvetica" SIZE="2" COLOR="#000066"><B>:msg</B></FONT></iIF ALIAS="ShowMsg"></TD><TD ALIGN=RIGHT><FONT FACE="Arial,Helvetica" SIZE="2" COLOR="#FFFFFF"><B>:AWPV</B></FONT></TD></TR><TR><TD VALIGN=TOP><FONT FACE="Arial,Helvetica" SIZE="-2"><B>Copyright &copy; 2000 adminware, llc</B></FONT></TD><TD ALIGN=RIGHT VALIGN=TOP><FONT FACE="Arial,Helvetica" SIZE="-2"><B><A HREF="http://adminware.com/" onMouseOver="status='adminware'; return true;" onMouseOut="status='';">http://adminware.com/</A></B></FONT></TD></TR></TABLE>

<iINCLUDE NAME="w:\shared\debugger.inc">
