#! /usr/bin/env bash

set -o errexit
set -o nounset
set -o pipefail

function _log()
{
  local type=$1
  local message=$2
  local date=$(date +"%Y-%m-%d %H:%M:%S")
  echo "[${date}] [${type}] ${message}"
}

function log_info()
{
  local message=$1
  _log "INFO" "${message}"
}

function log_error()
{
  local message=$1
  _log "ERROR" "${message}"
}

function main()
{
  local bin="solution"
  local makefile_target="all"

  local tests_type="test"
  if [[ "$#" -eq 2 ]]; then
    if [ $2 == "benchmark" ]; then
      tests_type=${2}
      bin="benchmark"
      makefile_target="benchmark"
    fi
  fi
  declare -a failed_tests

  log_info "Compiling..."
  if ! make ${makefile_target}; then
    log_error "ERROR: Failed to compile file."
    exit 1
  fi

  if [ ${tests_type} != "benchmark" ]; then
    log_info "Making unittest..."
    if ! make test ; then
      log_error "ERROR: Failed to run unittest."
      return 1
    fi
  fi
  
  local test_dir=tests
  rm -rf ${test_dir}
  mkdir -p ${test_dir}
  local tests_cnt=${1}

  log_info "Generating tests (examples for each test=[${tests_cnt}])..."
  if ! python3 tests_generator.py ${test_dir} ${tests_cnt} ${tests_type}; then
    log_error "ERROR: Failed to python generate tests."
    return 1
  fi

  last_answer="answer_file"
  for test_file in $(ls ${test_dir}/*.t); do
    log_info "Executing ${test_file}..."

    if [ ${tests_type} == "benchmark" ]; then
      if ! ./${bin} < ${test_file}; then
        log_error "ERROR"
        failed_tests+=( "${test_file}" )
        continue
      fi
    else
      if ! ./${bin} < ${test_file} >${last_answer}; then
        log_error "ERROR"
        failed_tests+=( "${test_file}" )
        continue
      fi

      local answer_file="${test_file%.*}"
      if ! diff -u "${answer_file}.a" ${last_answer} ; then
          echo "Failed"
          failed_tests+=( "${test_file}" )
      else
          echo "OK"
      fi
    fi
  done

  if [ ${#failed_tests[@]} -eq 0 ]; then
    log_info "No failed tests, hooray"
  else
    log_info "Failed test:"
    for test in ${failed_tests[@]}; do
      echo ${test}
    done
  fi
}

main $@
