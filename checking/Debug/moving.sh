if [ "$#" -ne 0 ]; then
	mv `git status -s | grep '??' | cut -f2 -d' '` ../views/checking/`git status -s | grep '??' | cut -f2 -d' '`  
	# alternative if you want files that are not tracked
else
	git status -s | grep ' M' | cut -f3 -d' ' | xargs tools/check-google-style.py 
fi
