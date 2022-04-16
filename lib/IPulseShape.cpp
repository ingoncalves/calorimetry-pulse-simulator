#include "IPulseShape.h"

unsigned int IPulseShape::TimeToIndex(const double & time) const {
  auto timeAnchor = std::lower_bound(m_tSeries.begin(), m_tSeries.end(), time);
  unsigned int timeIndex = timeAnchor != m_tSeries.end()
    ? std::distance(m_tSeries.begin(), timeAnchor)
    : m_tSeries.size() - 1;
  return timeIndex;
}

double IPulseShape::GetY(const double & time) const {
  if (m_tSeries.size() == 0 || m_ySeries.size() == 0) return 0;
  unsigned int timeIndex = TimeToIndex(time);
  return m_ySeries[timeIndex];
}
