//
// Created by sbruno on 24/07/2019.
//

#define CATCH_CONFIG_MAIN
#include "Include/catch.hpp"
#include "CIniFile.h"

CIniFile iniFile("./Files/Test","ini_test.ini");

TEST_CASE("Testing the constructor") {
    CIniFile iniFile2("C:/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/Files","ini_file.ini");
    REQUIRE(iniFile2.getPath() == "C:/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/Files/ini_file.ini");
    REQUIRE(iniFile.getPath() == "./Files/Test/ini_test.ini");
}

TEST_CASE("Testing the reader and the writer functions") {
    CIniFile iniFile2;
    CIniFile iniFile3("C:/Users/sbruno/Documents/Samuel/Varie/Uni/Lab Programmazione/FileINIProject/Files","ini_file.ini");
    CIniFile iniFile4("./Files/Test","empty_ini_test.ini");
    //Reader
    REQUIRE(iniFile4.ReadFile() == false);
    REQUIRE(iniFile3.ReadFile() == false);
    REQUIRE(iniFile2.ReadFile() == true);
    //Writer
    REQUIRE(iniFile4.WriteFile() == true);
    REQUIRE(iniFile3.WriteFile() == false);
    REQUIRE(iniFile2.WriteFile() == true);
    iniFile.ReadFile();
}

TEST_CASE("Testing the section functions") {
    REQUIRE(iniFile.FindSection("Prova") == 1);
    REQUIRE(iniFile.NumSections() == 5);
    REQUIRE(iniFile.AddSection("Unit Test") == 5);
    REQUIRE(iniFile.GetSection(5) == "Unit Test");
    REQUIRE(iniFile.NumKeyValuesInSection("Section 3 Test") == 2);
    REQUIRE(iniFile.DeleteSection("Test Scrittura") == true);
    REQUIRE(iniFile.DeleteSection("Unit Test") == true);
    REQUIRE(iniFile.NumSections() == 4);
    iniFile.WriteFile();
}

TEST_CASE("Testing the keys functions") {
    REQUIRE(iniFile.FindValue(0,"parameter_a") == 0);
    REQUIRE(iniFile.GetValueName("Section 3 Test",1) == "Type_ID_Integer");
    REQUIRE(iniFile.NumKeyCommentsInSection(1) == 2);
    REQUIRE(iniFile.AddKeyCommentInSection(1,"Commento per unit testing") == true);
    REQUIRE(iniFile.NumKeyCommentsInSection(1) == 3);
    REQUIRE(iniFile.GetKeyComment("Prova",0) == "Commento per Prova");
    REQUIRE(iniFile.GetKeyComment("Prova",2) == "Commento per unit testing");
    REQUIRE(iniFile.DeleteValueInSection("Prova","type_Integer") == true);
    REQUIRE(iniFile.DeleteCommentInSection("Section 1",0) == true);
    REQUIRE(iniFile.DeleteAllCommentsInSection("Prova") == true);
    iniFile.WriteFile();
}

TEST_CASE("Testing the header comments") {
    REQUIRE(iniFile.NumHeaderComments() == 4);
    REQUIRE(iniFile.GetHeaderComment(3) == "Questo invece e' un commento di scrittura per l'header");
    REQUIRE(iniFile.DeleteHeaderComment(1) == true);
    iniFile.DeleteAllHeaderComments();
    REQUIRE(iniFile.NumHeaderComments() == 0);
    iniFile.WriteFile();
}

TEST_CASE("Testing getters and setters for values that will be add in section") {
    REQUIRE(iniFile.SetValue("Chitarra","Chitarra a 1 corda","30") == true);
    REQUIRE(iniFile.SetValue("Chitarra","Chitarra a 2 corde","10",false) == false);
    REQUIRE(iniFile.SetValue("Chitarra","Chitarra a 6 corde","99",false) == true);
    REQUIRE(iniFile.GetValue<int>("Chitarra","Chitarra a 6 corde") == 99);
    REQUIRE(iniFile.GetValue<string>("Section 1","parameter_a") == "string.dll");
    REQUIRE(iniFile.GetValue<bool>("Prova","type_Bool") == 1);
    REQUIRE(iniFile.GetValue<bool>("Prova","type2_Bool") == 0);
    REQUIRE(iniFile.getBoolValue("off") == "0");
    REQUIRE(iniFile.getBoolValue("yes") == "1");
    REQUIRE(iniFile.getBoolValue("1") == "1");
    REQUIRE(iniFile.getBoolValue("0") == "0");
    REQUIRE(iniFile.getBoolValue("rosa") == "2");
    iniFile.WriteFile();
}

TEST_CASE("Testing path and filename functions") {
    CIniFile iniFile2("./Files/Test","empty_ini_test.ini");
    iniFile2.ChangePath("/opt/etc");
    REQUIRE(iniFile2.getPath() == "/opt/etc/empty_ini_test.ini");
    CIniFile iniFile3("./Files/Test","pippo.ini");
    iniFile3.RenameFileName("changedFilename","ini");
    REQUIRE(iniFile3.getPath() == "./Files/Test/changedFilename.ini");
    iniFile.WriteFile();
}