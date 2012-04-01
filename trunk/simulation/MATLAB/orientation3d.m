function [ euler ] = display_orientation_3d(q)
% Display orientation in 3D

% Compute the euler angles


euler = quaternion2euler(euler, q);
%roll = euler[0];
%pitch = euler[1];
%yaw = euler[2];

% Update rotation matrix
%R = [

function [ euler ] = quaternion2euler(q)
q = qnormalize(q);

q0 = q(1);
q1 = q(2);
q2 = q(3);
q3 = q(4);

roll = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 ^ 2 + q2 ^ 2));
pitch = arcsin(2 * (q0 * q2 - q1 * q3));
yaw = atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 ^ 2 + q3 ^ 2));

end