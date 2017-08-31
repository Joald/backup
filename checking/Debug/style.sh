if [ "$#" -ne 0 ]; then
	git status -s | grep '??' | cut -f2 -d' ' | xargs tools/check-google-style.py 
	# alternative if you want files that are not tracked
else
	git status -s | grep ' M' | cut -f3 -d' ' | xargs tools/check-google-style.py 
fi