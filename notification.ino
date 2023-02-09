#define SMTP_HOST ""
#define SMTP_PORT 587

#define AUTH_USER ""
#define AUTH_MAIL ""
#define AUTH_PASS ""

SMTPSession mail_smtp;

void init_notification()
{
}

void notification_send_mail(String recipient, String subject, String body)
{
  recipient.trim();
  
  if (recipient.length()) {
    ESP_Mail_Session session;
    SMTP_Message     message;
  
    session.server.host_name  = SMTP_HOST;
    session.server.port       = SMTP_PORT;
    session.login.email       = AUTH_MAIL;
    session.login.password    = AUTH_PASS;
    session.login.user_domain = "";

    session.time.ntp_server = "de.pool.ntp.org";
    session.time.gmt_offset = 1;

    if (time_is_dst()) {
      session.time.day_light_offset = 1;
    }else{
      session.time.day_light_offset = 0;
    }
  
    message.sender.name  = "PillBox";
    message.sender.email = AUTH_MAIL;
    message.subject      = subject;
    message.text.content = body.c_str();
    message.addRecipient(recipient, recipient);
  
    if (!mail_smtp.connect(&session)) {
      debug("Connect to SMTP-Server FAILED: " + mail_smtp.errorReason());
      return;
    }
  
    if (!MailClient.sendMail(&mail_smtp, &message)) {
      debug("Send mail FAILED" + mail_smtp.errorReason());
    } else {
      debug("Send mail OK");
    }
  }else{
    debug("Send mail FAILED - no recipient provided");
  }
}

void notification_send_signal(String message)
{
  if (get_setting("notifySignal").length() && get_setting("signalApiKey").length()) {

    message.replace("\n", " ");
    
    String url;
    url += "http://api.callmebot.com/signal/send.php?";
    url += "phone="   + notification_format_phone(get_setting("notifySignal"));
    url += "&apikey=" + get_setting("signalApiKey");
    url += "&text="   + message;

    debug("Sending Signal message to: " + notification_format_phone(get_setting("notifySignal")));

    debug("URL: " + url);
    
    http_get(url);
  }else{
    debug("Signal message FAILED (config incomplete)");
  }
}

String notification_format_phone(String phone)
{
  phone.trim();
  
  if (phone.length() > 0) {    
    if (phone.substring(0, 1) == "0") {
      return "+49" + phone.substring(1, phone.length());
    }else if (phone.substring(0, 1) == "+"){
      return phone;
    }
  }
  
  return "";
}
