bool sendToWait(uint8_t* data, size_t len, uint8_t dest) {
  int nextHop = getNextHop(dest);
  if (nextHop == -1) {
    // No known route; initiate discovery
    startRouteDiscovery(dest);
    nextHop = getNextHop(dest);
    if (nextHop == -1) return false; // Discovery failed
  }

  // Send via next hop
  return sendToNextHop(nextHop, data, len);
}
