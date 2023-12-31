#ifndef __usage_h__
#define __usage_h__

#include <vector>

std::vector<long long> readCPUTimes();

float cpuUsage();

void memUsage(std::vector<float>& vals);

void diskUsage(std::vector<float>& vals);

void networkUsage(std::vector<float>& vals);

#endif