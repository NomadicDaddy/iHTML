<iREM -- Save Changes -- >
<iIF COND=<iISDEF VAR="doUpdate"> ALIAS="doUpdate">
	<iREPLACE VAR="clientName" SRC="'" DST="''">
	<iREPLACE VAR="contactName" SRC="'" DST="''">
	<iREPLACE VAR="address1" SRC="'" DST="''">
	<iREPLACE VAR="address2" SRC="'" DST="''">
	<iREPLACE VAR="city" SRC="'" DST="''">
	<iREPLACE VAR="zipCode" SRC="'" DST="''">
	<iREPLACE VAR="officePhone" SRC="'" DST="''">
	<iREPLACE VAR="cellPhone" SRC="'" DST="''">
	<iREPLACE VAR="voiceMail" SRC="'" DST="''">
	<iREPLACE VAR="pagerPhone" SRC="'" DST="''">
	<iREPLACE VAR="faxPhone" SRC="'" DST="''">
	<iREPLACE VAR="emailAddress" SRC="'" DST="''">
	<iSET z="Contact info updated.">
	<iHTML DBNAME="adminware" LOGIN="adminware/zzz" SQL=`UPDATE clients SET clientName=':clientName', contactName=':contactName', address1=':address1', address2=':address2', city=':city', state_id=:state_id, zipCode=':zipCode', country_id=:country_id, officePhone=':officePhone', cellPhone=':cellPhone', voiceMail=':voiceMail', pagerPhone=':pagerPhone', faxPhone=':faxPhone', emailAddress=':emailAddress' WHERE id=:client_id ;` NOOUTPUT="Success" FAILURE=":i_sqlerrortext" OUTVAR="statusMsg">
	<iREPLACE VAR="statusMsg" SRC="[Microsoft][ODBC SQL Server Driver][SQL Server]Line 1: " DST="Update failed.">
	<iIF COND=<iSTRCMP SRC=":statusMsg" DST="Success"> ALIAS="setMsg"><iSET statusMsg=":z"></iIF ALIAS="setMsg">
</iIF ALIAS="doUpdate">

<iSQLMORE ALIAS="loadDB" SQL="
	SELECT clientName, contactName, address1, address2, city, state_id, zipCode, country_id, officePhone, cellPhone, voiceMail, pagerPhone, faxPhone, emailAddress 
	FROM clients (NOLOCK) 
	WHERE id=:client_id ;
">
<iSQLFETCH ALIAS="loadDB">

<FORM METHOD=POST ACTION=':thisPage'>
<INPUT TYPE=HIDDEN NAME="awpid" VALUE=":awpid">
<INPUT TYPE=HIDDEN NAME="client_id" VALUE=":client_id">
<INPUT TYPE=HIDDEN NAME="go" VALUE=":go">
<INPUT TYPE=HIDDEN NAME="showMenu" VALUE=":showMenu">
<INPUT TYPE=HIDDEN NAME="job" VALUE=":job">
<TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=2>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('clientName')" onMouseOut="noHelp()">Client Name</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="clientName" VALUE=":loadDB_clientName" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('contactName')" onMouseOut="noHelp()">Contact Name</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="contactName" VALUE=":loadDB_contactName" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('address1')" onMouseOut="noHelp()">Address</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="address1" VALUE=":loadDB_address1" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('address2')" onMouseOut="noHelp()">Address 2</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="address2" VALUE=":loadDB_address2" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('city')" onMouseOut="noHelp()">City</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="city" VALUE=":loadDB_city" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('state_id')" onMouseOut="noHelp()">State</A> &nbsp;</TD>
	<TD>
		<SELECT NAME="state_id">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT id, longDescr, name FROM _states (NOLOCK) ;">
		<iSQLFETCH ALIAS="loadDB">
		<iWHILE NOTALIAS=i_sqlempty>
				<OPTION VALUE=":loadDB_id" <iIF COND=<iSTRCMP SRC=":loadDB_state_id" DST=":loadDB_id">>SELECTED</iIF>>:loadDB_longDescr (:loadDB_name)</OPTION>
			<iSQLFETCH ALIAS="loadDB">
		</iWHILE ALIAS=i_sqlempty>
		</SELECT>
	</TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('zipCode')" onMouseOut="noHelp()">Zip Code</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="zipCode" VALUE=":loadDB_zipCode" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('country_id')" onMouseOut="noHelp()">Country</A> &nbsp;</TD>
	<TD>
		<SELECT NAME="country_id">
		<iSQLMORE ALIAS="loadDB" SQL="SELECT id, name, code FROM _countries (NOLOCK) ;">
		<iSQLFETCH ALIAS="loadDB">
		<iWHILE NOTALIAS=i_sqlempty>
				<OPTION VALUE=":loadDB_id" <iIF COND=<iSTRCMP SRC=":loadDB_country_id" DST=":loadDB_id">>SELECTED</iIF>>:loadDB_name (:loadDB_code)</OPTION>
			<iSQLFETCH ALIAS="loadDB">
		</iWHILE ALIAS=i_sqlempty>
		</SELECT>
	</TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('officePhone')" onMouseOut="noHelp()">Office Phone</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="officePhone" VALUE=":loadDB_officePhone" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('cellPhone')" onMouseOut="noHelp()">Cell Phone</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="cellPhone" VALUE=":loadDB_cellPhone" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('voiceMail')" onMouseOut="noHelp()">Voice Mail</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="voiceMail" VALUE=":loadDB_voiceMail" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('pagerPhone')" onMouseOut="noHelp()">Pager Phone</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="pagerPhone" VALUE=":loadDB_pagerPhone" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('faxPhone')" onMouseOut="noHelp()">Fax Phone</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="faxPhone" VALUE=":loadDB_faxPhone" SIZE=50></TD>
</TR>
<TR>
	<TD CLASS="tableHeading" WIDTH="1%" NOWRAP><A HREF="javascript:void(0);" onMouseOver="return popUpHelp('emailAddress')" onMouseOut="noHelp()">Email Address</A> &nbsp;</TD>
	<TD><INPUT TYPE=TEXT NAME="emailAddress" VALUE=":loadDB_emailAddress" SIZE=50></TD>
</TR>
<TR><TD COLSPAN=2 ALIGN=RIGHT><INPUT TYPE=SUBMIT NAME="doUpdate" VALUE="Update"></TD></TR>
</TABLE>
</FORM>
