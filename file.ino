void init_file_system() 
{
  if (LittleFS.begin()) {
    debug("LittleFS mounting OK");

    Dir dir = LittleFS.openDir("/");

    while (dir.next()) {
      debug(" FILE: " + dir.fileName() + "(" + String(dir.fileSize()) + ")");
    }
  } else {
    debug("LittleFS mounting FAILED");
  }
}


String file_read(String filePath)
{
  if (!LittleFS.exists(filePath)) {
    debug(filePath + " does not exist");
    return "";
  }
  
  File file = LittleFS.open(filePath, "r");

  if (file) {
    debug("Open file " + filePath + " OK");

    
    String fileContent;

    while (file.available()) {
      fileContent += char(file.read());
    }

    file.close();
    
    return fileContent;
  }else{
    debug("Open file " + filePath + " FAILED");
  }
}


bool file_write(String filePath, String fileContent)
{  
  File file = LittleFS.open(filePath, "w");

  int result = file.print(fileContent);

  file.close();

  if (result > 0) {
    return true;
  }else{
    return false;
  }
}
