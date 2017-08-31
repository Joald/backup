. goup.sh
if [ "$#" -ne 0 ]; then
    build/build_pnacl.sh native_player_widget
else
    build/build_pnacl.sh native_player_widget --no-sdk-gen
fi

