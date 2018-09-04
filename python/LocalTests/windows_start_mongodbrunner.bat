@echo off
echo "Setting MONGODB_PURGE=false"
set MONGODB_PURGE=false

echo "Starting mongodb-runner"
mongodb-runner start
echo "Started mongodb-runner"
pause
