declare -A pomo_options
pomo_options["work"]="45"
pomo_options["break"]="10"

pomodoro() {
	val=$1
	echo $val | lolcat
	timer ${pomo_options["$val"]}m
	spd-say "'$val' session done"
	notify-send --app-name=Pomodoro🍅 "'$val' session done 🍅"
}

start_pomodoro() {
	# Number of times to repeat the loop, default is 2
	if [ -n "$1" ] && [ "$1" -eq "$1" ] 2>/dev/null; then
		num_loops=$1
	else
		# Default loops
		num_loops=2
	fi

	for i in $(seq 1 $num_loops); do
		pomodoro "work"
		pomodoro "break"
	done
}
change_pomo() {
	if [ -n "$1" ] && [ -n "$2" ]; then
		pomo_options["$1"]="$2"
		echo "The $1 time has been changed to $2 minutes"
	else
		echo "Please provide valid parameters: change_pomo [work/break] [time_in_minutes]"
	fi
}

alias doro=start_pomodoro
alias wo="pomodoro 'work'"
alias br="pomodoro 'break'"
alias cp=change_pomo
