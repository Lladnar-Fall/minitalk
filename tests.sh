#!/bin/bash

# ----------------------------
# Simple Minitalk Test Script
# ----------------------------

echo "🔧 Starting server..."
./server &
SERVER_PID=$!

# Give server time to start
sleep 1

echo "🆔 Server PID: $SERVER_PID"
echo

# ----------------------------
# Basic tests
# ----------------------------

echo "▶ Test 1: Short message"
time ./client $SERVER_PID "Hello from minitalk"
echo

echo "▶ Test 2: Single character"
./client $SERVER_PID "A"
echo

echo "▶ Test 3: Empty string"
./client $SERVER_PID ""
echo

# ----------------------------
# Exact 100-character test
# ----------------------------

echo "▶ Test 4: Exactly 100 characters"
STR_100=$(printf 'A%.0s' {1..100})
time ./client $SERVER_PID "$STR_100"
echo

# ----------------------------
# Long message test
# ----------------------------

echo "▶ Test 5: Long message (500 characters)"
LONG=$(printf 'X%.0s' {1..500})
time ./client $SERVER_PID "$LONG"
echo

# ----------------------------
# Multiple messages
# ----------------------------

echo "▶ Test 6: Multiple messages"
for i in {1..5}; do
    ./client $SERVER_PID "Message number $i"
done
echo

# ----------------------------
# Cleanup
# ----------------------------

echo "🛑 Stopping server..."
kill $SERVER_PID
wait $SERVER_PID 2>/dev/null

echo "✅ Tests completed"