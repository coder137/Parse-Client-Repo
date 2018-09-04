@echo off
echo "Make sure you run this as ADMINISTRATOR"
echo "Setting MONGODB_PURGE=false"
set MONGODB_PURGE=false

echo "Starting mongodb-runner"
mongodb-runner start
echo "Started mongodb-runner"
pause
