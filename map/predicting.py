def predict_landing_point(point1, point2):
    """
    Predict the landing point along a linear trajectory defined by two points.
    
    Each point is a tuple of (latitude, longitude, altitude). The function
    finds the parameter t along the line from point1 to point2 for which 
    the altitude becomes zero, then computes the corresponding latitude 
    and longitude.
    
    Parameters:
        point1 (tuple): (lat1, lon1, alt1) - starting point.
        point2 (tuple): (lat2, lon2, alt2) - second point along the path.
    
    Returns:
        tuple or None: (landing_lat, landing_lon, 0) if an intersection exists,
        otherwise None if the line never intersects altitude zero.
    """
    lat1, lon1, alt1 = point1
    lat2, lon2, alt2 = point2
    
    # Calculate change in altitude
    delta_alt = alt2 - alt1

    # If there is no change in altitude, we cannot predict a unique landing point.
    if delta_alt == 0:
        return None

    # Solve for t where altitude becomes zero: alt1 + t * (alt2 - alt1) = 0
    t = -alt1 / delta_alt

    # If t is negative, the ground intersection is "behind" point1, 
    # so we return None (or choose to handle this case differently).
    if t < 0:
        return None

    # Compute the corresponding latitude and longitude.
    landing_lat = lat1 + t * (lat2 - lat1)
    landing_lon = lon1 + t * (lon2 - lon1)
    
    # By construction, altitude should be zero.
    landing_alt = alt1 + t * delta_alt

    return (landing_lat, landing_lon, landing_alt)