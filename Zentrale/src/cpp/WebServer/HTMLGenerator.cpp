//
// Created by philipp on 05.05.21.
//

#include "../../header/WebServer/HTMLGenerator.h"

HTMLGenerator::HTMLGenerator(KomponentenController *komponentenController) {
    komponentenController = KomponentenController::getInstance();
}

HTMLGenerator::~HTMLGenerator() {

}

string HTMLGenerator::generateMainPage() {
    return std::string();
}

string HTMLGenerator::generateHeader() {
    string header = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Zentrale</title>
</head>
<script>
    function openMainTab(evt, type) {
        // Declare all variables
        var i, tabcontent, tablinks;

        // Get all elements with class="tabcontent" and hide them
        tabcontent = document.getElementsByClassName("mainTabContent");
        for (i = 0; i < tabcontent.length; i++) {
            tabcontent[i].style.display = "none";
        }

        // Get all elements with class="tablinks" and remove the class "active"
        tablinks = document.getElementsByClassName("tabButton");
        for (i = 0; i < tablinks.length; i++) {
            tablinks[i].className = tablinks[i].className.replace(" active", "");
        }

        // Show the current tab, and add an "active" class to the button that opened the tab
        document.getElementById(type).style.display = "block";
        evt.currentTarget.className += " active";
    }
</script>)";
    return header;
}

string HTMLGenerator::generateMainTab() {
    string s = R"(    <article class="mainTabPage">
        <button class="tabButton" onclick="openMainTab(event, 'Erzeuger') ">Erzeuger</button>
        <button class="tabButton" onclick="openMainTab(event, 'Verbraucher') ">Verbraucher</button>
        <section class="mainTabContent" id="Erzeuger">
                <h3>Erzeuger</h3>")";
    s+= generateSubTabs("Erzeuger");
    s += R"(        </section>

        <section class="mainTabContent" id="Verbraucher">
            <h3>Verbraucher</h3>)";
    s+= generateSubTabs("Verbraucher");
    s+= R"(        </section>

    </article>)";
    return s;
}

string HTMLGenerator::generateSubTabs(string type) {
    string s = generateTableHead(type);
    std::vector<Komponente*> list;
    if (type == "Erzeuger")
        list = komponentenController->getErzeuger();
    else
        list = komponentenController->getVerbraucher();

    for (int i = 0; i < list.size(); ++i){
        std::map<unsigned long long, double> map = list[i]->getValues();
        string t = list[i]->getType();
        string name = list[i]->getName();
        int id = list[i]->getId();
        for (auto it = map.begin(); it != map.end(); ++it){
            s += generateTableRow(t, name, id, it->second, it->first);
        }
    }
    return s;
}

string HTMLGenerator::openBody() {
    string body = R"(<body onload="openMainTab(event, 'Erzeuger') ">)";
    return body;
}

string HTMLGenerator::closeBody() {
    string body = R"(</body>
</html>)";
    return body;
}

string HTMLGenerator::generateTableHead(string type) {
    string headerText = "";
    if (type == "Erzeuger")
        headerText = "Einspeisung";
    else
        headerText = "Verbrauch";

    string s = R"(<table style="width:100%">)";
    s += "<tr>";
    s += R"(<th>)";
    s += "Typ";
    s += R"(<\th>)";
    s += R"(<th>)";
    s += "Name";
    s += R"(<\th>)";
    s += R"(<th>)";
    s += "ID";
    s += R"(<\th>)";
    s += R"(<th>)";
    s += headerText;
    s += R"(<\th>)";
    s += R"(<th>)";
    s += "Zeitpunkt";
    s += R"(<\th>)";
    s += R"(<\tr>)";
    return s;
}

string HTMLGenerator::generateTableRow(string type, string name, int id, double value, unsigned long long time) {
    string s;
    s += "<tr>";
    s += "<td>";
    s += type;
    s += R"(<\td>)";
    s += "<td>";
    s += name;
    s += R"(<\td>)";
    s += "<td>";
    s += to_string(id);
    s += R"(<\td>)";
    s += "<td>";
    s += to_string(value);
    s += R"(<\td>)";
    s += "<td>";
    s += to_string(time);
    s += R"(<\td>)";
    s += R"(<\tr>)";
    return s;
}

string HTMLGenerator::closeTable() {
    return "</table>";
}