import argparse
import json
import logging
import os
import pickle
import subprocess
import traceback
from pprint import pprint

# Test commands
RUN_GAZEBO_COMMAND = "roslaunch wpr_simulation wpb_simple.launch"

GMAPPING_COMMAND = "roslaunch rushbot gmapping_test.launch"
SAVE_MAP_COMMAND = "rosrun map_server map_saver -f $(roscd rushbot ; pwd)/data/map"

ADD_WAYPOINT_COMMAND = "roslaunch waterplus_map_tools add_waypoint.launch"
SAVE_WAYPOINT_COMMAND = "rosrun waterplus_map_tools wp_saver -f $(roscd rushbot ; pwd)/data/waypoints.xml"
TEST_WAYPOINT_COMMAND = "roslaunch rushbot waypoint_test.launch"

NAV_TEST_COMMAND = "roslaunch rushbot nav_test.launch"


def keyboard_control():  # use cpp test instead
    # print("Start keyboard control test")
    pass


def gmapping():
    completed_processes = [
        subprocess.run(RUN_GAZEBO_COMMAND),
        subprocess.run(GMAPPING_COMMAND),
        subprocess.run(SAVE_MAP_COMMAND)
    ]
    # Check returncode, stdout, etc
    pprint(completed_processes)


def add_waypoint():
    completed_processes = [
        subprocess.run(RUN_GAZEBO_COMMAND),
        subprocess.run(ADD_WAYPOINT_COMMAND),
        subprocess.run(SAVE_WAYPOINT_COMMAND),
        subprocess.run(TEST_WAYPOINT_COMMAND)
    ]
    pprint(completed_processes)


def navigation():  # GUI test navigation
    completed_processes = [
        subprocess.run(RUN_GAZEBO_COMMAND),
        subprocess.run(NAV_TEST_COMMAND)
    ]
    pprint(completed_processes)


def voice_recognition():  # manual test
    pass


def test_modules():
    test_names = [
        # "keyboard_control",
        "gmapping",
        "add_waypoint",
        "navigation",
        "voice_recognition",
    ]
    while True:
        print("------------------------------")
        print("Available tests: ")
        for t_id, test_name in enumerate(test_names):
            print("{}: {}".format(t_id, test_name))
        print("Please input test id:")
        test_id = int(input())
        globals()[test_names[test_id]]()  # call method by name


if __name__ == "__main__":
    test_modules()
