<!--
adminware File Uploader v1.3.227.1
Copyright � 1999-2002 adminware, llc
http://adminware.com/
-->

<iSET AWPV="File Uploader v1.3.227.1">

<iINCLUDE NAME="w:\ifuncs\errorHandler.inc">
<iSET fileSize="Unavailable" zOrigFile="Unavailable" cfgPass=1>
<iDEFAULT NAME="fucfg" VALUE="fileuploader.cfg">
<iINCLUDE NAME=":fucfg">

<iFUNCTION ALIAS="doBad">
	<iIF COND=<iSTRIN SRC=":BADURL" DST="?"> ALIAS="args">
		<iREDIR URL=':BADURL&errMsg=:ERRMSG'>
	<iELSE ALIAS="args">
		<iREDIR URL=':BADURL?errMsg=:ERRMSG'>
	</iIF ALIAS="args">
</iFUNCTION ALIAS="doBad">

<iIF EXPR='<iSTRIN SRC=":i_priv_post" DST="Content-Type:"> AND <iSTRIN SRC=":i_priv_post" DST="Content-Disposition: form-data"> AND NOT <iSTRIN SRC=":i_priv_post" DST='filename=""'> AND NOT <iSTRCMP SRC=":origFile" DST="">' ALIAS="fileUp">
	<iGETMIMENAME OUTVAR="mimeName">
	<iREPLACE VAR="mimeName" SRC="/" DST="\">
	<iSTRIN SRC=":mimeName" DST="\" OUTVAR="slashPos">
	<iIF NOTCOND=<iSTRCMP SRC=":slashPos" DST="0"> ALIAS="isPathed">
		<iSTRREV SRC=":mimeName" OUTVAR="revMimeName">
		<iSTRREV SRC=`<iSTRLEFT SRC=":revMimeName" NUM=<iEVAL EXPR='<iSTRIN SRC=":revMimeName" DST="\"> - 1'>>` OUTVAR="origFile">
	<iELSE ALIAS="isPathed">
		<iSET origFile=":mimeName">
	</iIF ALIAS="isPathed">
	<iSTRIN SRC=":origFile" DST="." OUTVAR="firstDot">
	<iSTRSPAN SRC=":origFile" FIRST=<iEVAL EXPR=':firstDot + 1'> NUM=<iEVAL EXPR='<iSTRLEN SRC=":origFile"> - :firstDot + 1'> OUTVAR="origExt">
	<iURLENCODE SRC=':origFile' OUTVAR='zOrigFile'>
	<iIF COND=<iSTRCMP SRC=":goodExt" DST=""> ALIAS="allExtensions">
		<iSET goodExt=":origExt">
	</iIF ALIAS="allExtensions">
	<iIF COND=<iSTRIN SRC=":goodExt" DST=":origExt"> ALIAS="goodExtension">
		<iSET cfgPass=2>
		<iINCLUDE NAME=":fucfg">
		<iFILE NAME=":saveAs" OP=EXISTS OUTVAR="fileExists">
		<iIF EXPR='NOT :fileExists OR (:fileExists AND :overwrite)' ALIAS="overwriteFile">
			<iIF EXPR=':fileExists' ALIAS="delFile">
				<iFILE NAME=":saveAs" OP=DELETE>
			</iIF ALIAS="delFile">
			<iGETMIMEFILE FILENAME=":saveAs" NAME=<iGETMIMENAME> EHANDLE=INLINE>
			<iFILEINFO FILE=":saveAs" INFO=SIZE OUTVAR="fileSize">
			<iIF EXPR=':fileSize GT 0' ALIAS="notEmpty">
				<iIF EXPR=':doNotify'>
					<iMAIL ADDRESS=":notifyTo" FROM=":notifyFrom" SUBJECT=":notifySubj">File Uploaded:	':origFile' -> ':saveAs'	Size: :fileSize bytes</iMAIL>
				</iIF>
				<iSET cfgPass=2>
				<iINCLUDE NAME=":fucfg">
				<iREDIR URL=':goodURL'>
			<iELSE ALIAS="notEmpty">
				<iFUNCCALL ALIAS="doBad" ERRMSG="File%20has%20Zero%20Bytes" BADURL=":badURL">
			</iIF ALIAS="notEmpty">
		<iELSE ALIAS="overwriteFile">
			<iFUNCCALL ALIAS="doBad" ERRMSG="Filename%20Already%20Exists%20-%20Rename%20File%20and%20Try%20Again" BADURL=":badURL">
		</iIF ALIAS="overwriteFile">
	<iELSE ALIAS="goodExtension">
		<iFUNCCALL ALIAS="doBad" ERRMSG="Bad%20Extension" BADURL=":badURL">
	</iIF ALIAS="goodExtension">
<iELSE ALIAS="fileUp">
	<iFUNCCALL ALIAS="doBad" ERRMSG="File%20Not%20Uploaded" BADURL=":badURL">
</iIF ALIAS="fileUp">

<iHEAPDUMP HEAP=LOCAL OUTVAR="dump">
<iREPLACE VAR="dump" SRC="<BR>" DST=":i$crlf">
<iMAIL ADDRESS=":notifyTo" FROM=":notifyFrom" SUBJECT="File Uploader Error"><iDATETIME> File Uploader Error = :errMsg
Error Number  = :i_error
Error Message = :i_errortext
Error Details = :i_errordetail
-----
:dump
</iMAIL>

<iFUNCCALL ALIAS="doBad" ERRMSG="Unknown%20Error" BADURL=":badURL">
