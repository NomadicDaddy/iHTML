<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR="#A0B8C8">
  <TD><FONT FACE="Arial,Helvetica" SIZE="2" COLOR="#FFFFFF"><B>&nbsp;AuthManager

  <iIF COND=<iISDEF VAR="Area">><iHTML DBNAME=":dsn" LOGIN=":am_login" SQL="SELECT Name FROM _Areas WHERE ID = :Area ;" OUTPUT=":1" OUTVAR="AreaName"></iIF>

  <iSWITCH ALIAS="go">
  <iCASE ALIAS="go" VALUE="Manage Existing Users">
    <iDEFAULT NAME="ViewFrom" VALUE="1">
    <iSET SubArea=`Viewing Users :ViewFrom - <iEVAL EXPR=':ViewFrom + :MaxItems - 1'>`>
    <iIF EXPR='<iISDEF VAR="DoDelete.x"> OR <iISDEF VAR="DoDelete">'><iSET SubArea="Deleting User"></iIF>
    <iIF COND=<iISDEF VAR="DoUpdate">><iSET SubArea="Updating User"></iIF>
    <iIF EXPR='<iISDEF VAR="DoEdit.x"> OR <iISDEF VAR="DoEdit">'><iSET SubArea="Editing User"></iIF>
    <iSET context="Users">    - Managing Existing Users of ':AreaName' Area - :SubArea
  </iCASE ALIAS="go">
  <iCASE ALIAS="go" VALUE="Add a User">           <iSET context="NewUser">  - Adding a New User to ':AreaName' Area      </iCASE ALIAS="go">
  <iCASE ALIAS="go" VALUE="Manage Settings">      <iSET context="Settings"> - Managing ':AreaName' Area Settings         </iCASE ALIAS="go">
  <iCASE ALIAS="go" VALUE="Manage Fields">        <iSET context="Fields">   - Managing ':AreaName' Field Definitions     </iCASE ALIAS="go">
  <iCASE ALIAS="go" VALUE="Change Password">      <iSET context="Change">   - Change Password                            </iCASE ALIAS="go">
  <iCASE ALIAS="go" VALUE=DEFAULT>                <iSET context="Main">                                                  </iCASE ALIAS="go">
  </iSWITCH ALIAS="go">

  </B></FONT></TD>
<iREMBLOCK>
  <TD WIDTH=1% ALIGN=RIGHT><A HREF="javascript:AreaNameHelp(':context')"><FONT FACE="Arial,Helvetica" SIZE="2" COLOR="#FFFFFF"><B>Help</B></FONT></A></TD>
  <TD WIDTH=1% ALIGN=RIGHT><A HREF="/authmanager/faq.ihtml?ShowCat=:context" TARGET="_blank"><FONT FACE="Arial,Helvetica" SIZE="2" COLOR="#FFFFFF"><B>FAQ</B></FONT></A>&nbsp;</TD>
</iREMBLOCK>
</TR></TABLE>
