
import os

from ament_index_python.packages import get_package_prefix

import launch.actions


def generate_launch_description():

    server = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_service'),
		'lib/minimal_service/service_main')], output='screen')

    node1 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    node2 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    node3 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    node4 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    node5 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    node6 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    node7 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    node8 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    node9 = launch.actions.ExecuteProcess(
        cmd=[os.path.join( get_package_prefix('minimal_publisher'),
		'lib/minimal_publisher/publisher_lambda')], output='screen')

    ld = launch.LaunchDescription()

    ld.add_action(server)
    ld.add_action(node1)
    ld.add_action(node2)
    ld.add_action(node3)
    ld.add_action(node4)
    ld.add_action(node5)
    ld.add_action(node6)
    ld.add_action(node7)
    ld.add_action(node8)
    ld.add_action(node9)

    return ld
