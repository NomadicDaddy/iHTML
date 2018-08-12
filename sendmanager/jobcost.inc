<iREM -- Calculate Run Charge -- >
<iDEFAULT NAME="costLevel" VALUE="">
<iIF EXPR='1 GT :sendPieces'><iSET sendPieces=1></iIF>
<iINCLUDE NAME="w:\sendmanager\jobcost.ifunc">
<iFUNCCALL ALIAS="jobCost" APPCONN=":appConn" PIECES=":sendPieces" BYTES=":loadDB_mailSize" GROUP=":costLevel" OUTVAR="baseRunCharge">
<iSET runDiscount=0 f1=0 f2=0 f3=0 f4=0 f5=0 f6=0 f7=0>
<iIF EXPR='NOT <iSTRIN SRC=":loadDB_body" DST="<:"> AND NOT <iSTRIN SRC=":loadDB_htmlbody" DST="<:">'><iSET f1=5></iIF>
<iIF EXPR='<iSTRCMP SRC=":loadDB_postSub" DST=""> AND <iSTRCMP SRC=":loadDB_postUnsub" DST=""> AND <iSTRCMP SRC=":loadDB_postBounce" DST="">'><iSET f2=8></iIF>
<iIF EXPR='NOT <iSTRIN SRC=":loadDB_body" DST="<:Link"> AND NOT <iSTRIN SRC=":loadDB_htmlbody" DST="<:Link">'><iSET f3=10></iIF>
<iIF EXPR='NOT <iSTRIN SRC=":loadDB_body" DST="<:ViewTracker"> AND NOT <iSTRIN SRC=":loadDB_htmlbody" DST="<:ViewTracker">'><iSET f4=2></iIF>
<iIF NOTCOND=<iSTRCMP SRC=":loadDB_returnPath" DST="">><iSET f5=5></iIF>
<iIF EXPR='<iSTRCMP SRC=":loadDB_allowSelfSub" DST="0"> AND <iSTRCMP SRC=":loadDB_allowSelfUnsub" DST="0">'><iSET f6=5></iIF>
<iIF EXPR='<iSTRIN SRC=":loadDB_body" DST="mailexec" CASE=FALSE> OR <iSTRIN SRC=":loadDB_htmlbody" DST="mailexec" CASE=FALSE>'><iSET f7=-2></iIF>
<iEVAL EXPR='(:f1 + :f2 + :f3 + :f4 + :f5 + :f6 + :f7) * -0.01' PREC=2 OUTVAR="runDiscount">
<iEVAL EXPR=':baseRunCharge + (:baseRunCharge * :runDiscount)' PREC=2 OUTVAR="runCharge">
