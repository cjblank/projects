#!/bin/bash
usage() {
  echo "Usage: $0 [ OPTIONS ] [ -n USERNAME ] [ -m MOUNTPOINT ]"
  echo "OPTIONS:"
  echo " -r read-only"
  echo " -u unmount"
  exit 1
}

ARGS="allow_other"
while getopts run:m: option
do
  case "${option}" in
    r) ARGS+=",ro";;
    u) UN=" ";;
    n) USER=${OPTARG};;
    m) MOUNT=${OPTARG};;
    \?);;
    *) usage;;
  esac
done


if [ -n "${UN}" ]; then
  if [ -z ${MOUNT} ]; then
    usage
  else
    fusermount -u ${MOUNT}
  fi
else
  if [ -z "${USER}" ] || [ -z "${MOUNT}" ]; then
    usage
  else
    sshfs ${USER}@capstone1.computing.clemson.edu:/data/ ${MOUNT} -o ${ARGS}
  fi
fi
