#!/bin/bash

envsubst < ${CONF_NAME} > /home/chat2Data/chat2Data.conf

exec ${BIN_NAME}
