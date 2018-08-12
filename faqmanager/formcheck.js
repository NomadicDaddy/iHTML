<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript"><!--
function newQFormCheck(form) {
	if (form.notifyEmail.value.length == 0) {
		alert("Please enter an email address.")
		form.notifyEmail.focus()
		return false;
	}
	if (form.notifyEmail.value.length > 0) {
		i=form.notifyEmail.value.indexOf("@")
		j=form.notifyEmail.value.indexOf(".",i)
		k=form.notifyEmail.value.indexOf(",")
		kk=form.notifyEmail.value.indexOf(" ")
		jj=form.notifyEmail.value.lastIndexOf(".")+1
		len=form.notifyEmail.value.length
		if ((i>0) && (j>(1+1)) && (k==-1) && (kk==-1) && (len-jj >=2) && (len-jj<=3)) { }
		else {
			alert("Please correct the email address.\n\n" + form.notifyEmail.value + " is not valid.")
			form.notifyEmail.focus()
			return false;
		}
	}
	if (form.nQuestion.value == "" || form.nQuestion.value.length < 5) {
		alert("Please enter a valid question.");
		form.nQuestion.focus()
		return false;
	}
}
function sFormCheck(form) {
	if (form.searchFor.value == "" || form.searchFor.value.length < 3) {
		alert("Please enter a search term of three characters or more.");
		form.searchFor.focus()
		return false;
	}
}
//--></SCRIPT>
