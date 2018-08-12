<iREMBLOCK>
parseArgs Include v1.62.312.2
Created by Vegard Riseng and Phillip Beazley.

Syntax:
 [iSET TYPE="AUTO, POST or GET"]		(AUTO)
 [iSET DEBUG="TRUE or FALSE"]			(FALSE)
 [iSET QUERYSTRING="TRUE or FALSE"]	(FALSE)
 [iSET BEAUTIFY="TRUE or FALSE"]		(FALSE)
 [iSET GENFORMINPUT="TRUE or FALSE"]	(FALSE)
 [iSET NOPASSTHRU="fields not to pass"]	()
 [iSET PASSTHRU="fields to only pass"]	()
 [iSET NULLVIEW="null value display"]	([null])
 iINCLUDE NAME="parseArgs.inc"

Revision History:
 1.0.181.1	-- Original. [VR]
 1.1.182.1	-- Minor format change.  Addition of null value handling and argView. [PB]
 1.1.182.2	-- Minor optimizations.  Changed 'var' to 'arg_'.  Added 'export' of arguments for external use. [PB]
 1.2.23.1		-- Addition of POST/GET/POST+GET handling. [PB]
 1.3.99.1		-- Addition of QUERYSTRING option and output. [PB]
 1.4.200.1	-- Minor fix and added maxArgLength, maxValLength. [PB]
 1.5.209.1	-- Rewrote parser engine. [VR]
 1.5.209.2	-- Addition of handler for variablenames with spaces (user 404 fix). [VR]
 1.5.209.3	-- Speed optimizations of "super parser". [VR]
 1.5.210.1	-- Addition of BEAUTIFY option.  Stores the original var name in 'old_#' if it contained special chars. [VR]
 1.6.310.1	-- Addition of GENFORMINPUT option.  Creates pass-thru form input strings excluding fields in NOPASSTHRU or including only fields in PASSTHRU. [PB]
 1.61.310.1	-- Addition of NULLVIEW option.  This is the value passed if the variable doesn't have a value. [PB]
 1.62.312.1	-- Fixed problem with QUERYSTRING and added support for NOPASSTHRU/PASSTHRU. [PB]
 1.62.312.2	-- Worked around problem with urlDecode returning non-printable extraneous characters. [PB]
</iREMBLOCK>

<iFORMAT>

<iFUNCTION ALIAS="urlDecode">
	<iREM --- Do the special cases first --->
	<iREPLACE SRC="+" DST=" " VAR="decode">
	<iREPLACE SRC="%22" DST='"' VAR="decode">
	<iREPLACE SRC="%23" DST="#" VAR="decode">
	<iREPLACE SRC="%27" DST="'" VAR="decode">
	<iREPLACE SRC="%60" DST="`" VAR="decode">
	<iREPLACE SRC="%25" DST="&#37;" VAR="decode">
	<iSTRIN SRC=":decode" DST="%" OUTVAR="doReplace">
	<iWHILE ALIAS="doReplace">
		<iSTRSPAN FIRST=<iEVAL EXPR=":doReplace+1"> NUM="2" SRC=":decode" OUTVAR="hexValue">
		<iBASECONV FROM="H" TO="D" VALUE=":hexValue" OUTVAR="decValue">
		<iREPLACE SRC="%:hexValue" DST='<iCHR ASC=":decValue">' VAR="decode">
		<iSTRIN SRC=":decode" DST="%" OUTVAR="doReplace">
	</iWHILE ALIAS="doReplace">
	<iREPLACE SRC="&#37;" DST="%" VAR="decode">
	:decode
</iFUNCTION>

<iREM -- Setup Defaults -- >
<iDEFAULT NAME="TYPE" VALUE="AUTO">
<iDEFAULT NAME="DEBUG" VALUE="FALSE">
<iDEFAULT NAME="QUERYSTRING" VALUE="FALSE">
<iDEFAULT NAME="BEAUTIFY" VALUE="FALSE">
<iDEFAULT NAME="GENFORMINPUT" VALUE="FALSE">
<iDEFAULT NAME="NOPASSTHRU" VALUE="">
<iDEFAULT NAME="PASSTHRU" VALUE="">
<iDEFAULT NAME="NULLVIEW" VALUE="[null]">
<iSET argCount=0 argMsg="" passQueryString="" maxArgLength=0 maxValLength=0 formInputString="">
<iIF NOTCOND=<iSTRCMP SRC=":NOPASSTHRU" DST="">><iSET PASSTHRU=""></iIF>

<iREM -- Check Directives -- >
<iIF EXPR='NOT <iSTRCMP SRC=":QUERYSTRING" DST="TRUE"> AND NOT <iSTRCMP SRC=":QUERYSTRING" DST="FALSE">'><iSET QUERYSTRING="FALSE"></iIF>
<iIF EXPR='(NOT <iSTRCMP SRC=":TYPE" DST="AUTO"> AND NOT <iSTRCMP SRC=":TYPE" DST="POST"> AND NOT <iSTRCMP SRC=":TYPE" DST="GET">) OR	(NOT <iSTRCMP SRC=":DEBUG" DST="TRUE"> AND NOT <iSTRCMP SRC=":DEBUG" DST="FALSE">)' ALIAS="checkDirectives">
	<iSETERROR ERROR="710" DETAIL="TYPE = :TYPE, DEBUG = :DEBUG">
</iIF ALIAS="checkDirectives">

<iREM -- Build Argument List -- >
<iCASE ALIAS="TYPE" VALUE="AUTO">
	<iIF EXPR='<iSTRLEN SRC=":i_query_string"> GT 0 AND <iSTRLEN SRC=":i_priv_post"> GT 0' ALIAS="isQ">
		<iSET args=":i_priv_post&:i_query_string">
	<iELSE ALIAS="isQ">
		<iSET args=":i_priv_post:i_query_string">
	</iIF ALIAS="isQ">
</iCASE ALIAS="TYPE">
<iCASE ALIAS="TYPE" VALUE="POST">
	<iSET args=":i_priv_post">
</iCASE ALIAS="TYPE">
<iCASE ALIAS="TYPE" VALUE="GET">
	<iSET args=":i_query_string">
</iCASE ALIAS="TYPE">

<iREM -- Do Parsing -- >
<iIF COND=<iSTRLEN SRC=":args"> ALIAS="hasArgs">
	<iSET args="':args'">
	<iREPLACE SRC="&" DST="','" VAR="args">
	<iLISTCREATE NAME="argList" SRC="args" TYPE=VARIABLE DELIM="'" SEP=",">
	<iLISTGET NAME="argList" OP=COUNT DELIM="'" SEP="," OUTVAR="argCount">
	<iLOOP INITIAL=1 FINAL=:argCount ALIAS="argNum">
		<iLISTGET NAME="argList" INDEX=:argNum OP=GETAT OUTVAR="currentArg">
		<iSET currentArg="':currentArg'">
		<iREPLACE SRC="=" DST="','" VAR="currentArg">
		<iLISTCREATE NAME="currentArgList" SRC="currentArg" TYPE=VARIABLE DELIM="'" SEP=",">
		<iLISTGET NAME="currentArgList" OP=COUNT DELIM="'" SEP="," OUTVAR="currentArgCount">
		<iLISTGET NAME="currentArgList" INDEX=1 OP=GETAT DELIM="'" SEP="," OUTVAR="argName">
		<iIF EXPR='<iSTRIN SRC=":argName" DST="+"> GT 0 OR <iSTRIN SRC=":argName" DST="%"> GT 0' ALIAS="spaceInArgName">
			<iREM --- "Super-parser" starts --->
			<iIF COND=":BEAUTIFY" ALIAS="beautify">
				<iEQ NAME="oldArg" VALUE="old_:argNum">
				<iFUNCCALL ALIAS="urlDecode" DECODE=":argName" OUTVAR="beautified">
				<iSTRKEEP SRC=":beautified" OMIT=" 	:i$crlf" OUTVAR="beautified">
				<iEQ NAME=":oldArg" VALUE=":beautified">
			</iIF ALIAS="beautify">
			<iREPLACE SRC="+" DST="_" VAR="argName">
			<iSTRIN SRC=":argName" DST="%" OUTVAR="doReplace">
			<iWHILE ALIAS="doReplace">
				<iSTRSPAN FIRST=<iEVAL EXPR=":doReplace+1"> NUM="2" SRC=":argName" OUTVAR="hexValue">
				<iREPLACE SRC="%:hexValue" DST="" VAR="argName">
				<iSTRIN SRC=":argName" DST="%" OUTVAR="doReplace">
			</iWHILE ALIAS="doReplace">
			<iSET argValue="">
			<iIF EXPR=":currentArgCount GE 2" ALIAS="valueNotNull">
				<iLISTGET NAME="currentArgList" INDEX=2 OP=GETAT DELIM="'" SEP="," OUTVAR="currentArgValue">
				<iFUNCCALL ALIAS="urlDecode" DECODE=":currentArgValue" OUTVAR="argValue">
				<iSTRKEEP SRC=":argValue" OMIT=" 	:i$crlf" OUTVAR="argValue">
			</iIF ALIAS="valueNotNull">
			<iEQ NAME=":argName" VALUE=":argValue">
		</iIF ALIAS="spaceInArgName">
		<iEQ NAME="varName" VALUE="arg_:argNum">
		<iEQ NAME=":varName" VALUE=":argName">
		<iUNDEFINE currentArgList>
	</iLOOP ALIAS="argNum">
</iIF ALIAS="hasArgs">

<iIF COND=":argCount" ALIAS="haveArgs">
	<iSET argMsg=":argCount (argCount) arguments were submitted:<BR><BR>">
	<iLOOP INITIAL=1 FINAL=:argCount>
		<iEQ NAME="variable" VALUE=":arg_:i_loop" EVAL=TRUE>
		<iEQ NAME="value" VALUE="::variable" EVAL=TRUE>
		<iIF EXPR='<iSTRCMP SRC=":value" DST="::variable"> OR <iSTRCMP SRC=":value" DST="">' ALIAS="isNull"><iSET value=":nullView"></iIF ALIAS="isNull">
		<iEQ NAME="val_:i_loop" VALUE=":value">
		<iSTRLEN SRC=":variable" OUTVAR="curArgLength">
		<iIF EXPR=':curArgLength > :maxArgLength'><iSET maxArgLength=:curArgLength></iIF>
		<iSTRLEN SRC=":value" OUTVAR="curValLength">
		<iIF EXPR=':curValLength > :maxValLength'><iSET maxValLength=:curValLength></iIF>
		<iSTRCAT DST="argMsg" SRC=" -- (arg_:i_loop) :variable = (val_:i_loop) ':value'<BR>">
		<iIF EXPR=':GENFORMINPUT OR :QUERYSTRING' ALIAS="genStrings">
			<iIF NOTCOND=<iSTRCMP SRC=":NOPASSTHRU" DST=""> ALIAS="doPass">
				<iIF NOTCOND=<iSTRIN SRC=":NOPASSTHRU" DST=":variable"> ALIAS="allow">
					<iSTRCAT DST="formInputString" SRC=`<INPUT TYPE=HIDDEN NAME=":variable" VALUE=":value">`>
					<iSTRCAT DST="passQueryString" SRC="?:variable=:value">
				</iIF ALIAS="allow">
			<iELSEIF NOTCOND=<iSTRCMP SRC=":PASSTHRU" DST=""> ALIAS="doPass">
				<iIF COND=<iSTRIN SRC=":PASSTHRU" DST=":variable"> ALIAS="allow">
					<iSTRCAT DST="formInputString" SRC=`<INPUT TYPE=HIDDEN NAME=":variable" VALUE=":value">`>
					<iSTRCAT DST="passQueryString" SRC="?:variable=:value">
				</iIF ALIAS="allow">
			<iELSE ALIAS="doPass">
				<iSTRCAT DST="formInputString" SRC=`<INPUT TYPE=HIDDEN NAME=":variable" VALUE=":value">`>
				<iSTRCAT DST="passQueryString" SRC="?:variable=:value">
			</iIF ALIAS="doPass">
		</iIF ALIAS="genStrings">
	</iLOOP>
<iELSEIF NOTCOND=<iISDEF VAR="argMsg"> ALIAS="haveArgs">
	<iSET argMsg="No args submitted!<BR>">
</iIF ALIAS="haveArgs">

<iREM -- Output Results -- >
<iIF COND=<iSTRCMP SRC=":DEBUG" DST="TRUE"> ALIAS="showArgs">
	:argMsg
<iELSEIF COND=<iSTRCMP SRC=":QUERYSTRING" DST="TRUE"> ALIAS="showArgs">
	:passQueryString
<iELSEIF COND=<iSTRCMP SRC=":GENFORMINPUT" DST="TRUE"> ALIAS="showArgs">
	:formInputString
<iELSE ALIAS="showArgs">
	:argCount
</iIF ALIAS="showArgs">

</iFORMAT>
