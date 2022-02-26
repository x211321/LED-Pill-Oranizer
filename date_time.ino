#define NTP_SERVER "de.pool.ntp.org"
#define TIMEZONE "CET-1CEST,M3.5.0,M10.5.0/3" // https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv

void init_date_time()
{
  configTime(TIMEZONE, NTP_SERVER);
}

String time_get_hours_from_time_string(String time_string)
{
  time_string.trim();
  
  if (time_string.length() >= 5) {
    return time_string.substring(0, 2);
  }
}

String time_get_minutes_from_time_string(String time_string)
{
  time_string.trim();
  
  if (time_string.length() >= 5) {
    return time_string.substring(3, 5);
  }
}

bool time_is_dst()
{
  time_t now_;
  tm tm_;

  time(&now_);
  localtime_r(&now_, &tm_);

  if (tm_.tm_isdst > 0) {
    return true;
  }else{
    return false;
  }
}
