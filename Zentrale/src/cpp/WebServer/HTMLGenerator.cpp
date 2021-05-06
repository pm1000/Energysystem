//
// Created by philipp on 05.05.21.
//

#include "../../header/WebServer/HTMLGenerator.h"

HTMLGenerator::HTMLGenerator(){
    komponentenController = KomponentenController::getInstance();
};

HTMLGenerator::~HTMLGenerator() {

}

string HTMLGenerator::generateMainPage() {
    string s = generateHeader(true, "Zentrale");
    s += openBody(true);
    s += generateMainTab();
    s += closeBody();
    std::replace(s.begin(), s.end(), '\n', ' ');

    return s;
}

string HTMLGenerator::generateSubPage(string& name, bool history) {
    Komponente* k = komponentenController->getKomponenteByName(name);

    //check if the requested component is part of the system
    if (k == nullptr)
        return "ALARM! Es gibt keine Komponente mit dem Namen \"" + name + "\".";

    string type = "Erzeuger";
    if (k->getType() == "Haushalt" || k->getType() == "Unternehmen");
        type = "Verbraucher";

    string s = generateHeader(false, name);
    s += openBody(false);

    string t = k->getType();

    if (history){
        s += generateTableHead(type);
        std::map<unsigned long long, double> map = k->getValues();
        for (auto it = map.begin(); it != map.end(); ++it){
            s += generateTableRow(t, name, k->getId(), it->second, it->first);
        }
        s += closeTable();
    }

    s += closeBody();
    std::replace(s.begin(), s.end(), '\n', ' ');

    return s;
}

string HTMLGenerator::generateHeader(bool mainPage, string title) {
    string header = R"(<!DOCTYPE html>
<html lang="en">
<head>
  <link href="https://unpkg.com/material-components-web@latest/dist/material-components-web.min.css" rel="stylesheet">
  <script src="https://unpkg.com/material-components-web@latest/dist/material-components-web.min.js"></script>
    <meta charset="UTF-8">
    <title>)";
    header += title;
    header += R"(</title> </head>)";

    if (mainPage)
        header += R"(
        <script>
        function openMainTab(evt, type) {

        var i, tabcontent, tablinks;


        tabcontent = document.getElementsByClassName('mainTabContent');
        for (i = 0; i < tabcontent.length; i++) {
            tabcontent[i].style.display = 'none';
        }


        tablinks = document.getElementsByClassName('tabButton');
        for (i = 0; i < tablinks.length; i++) {
            tablinks[i].className = tablinks[i].className.replace(' active', '');
        }

        document.getElementById(type).style.display = 'block';
        evt.currentTarget.className += ' active';
        }
        </script>)";
    return header;
}

string HTMLGenerator::generateMainTab() {
    string s = R"(    <article class="mainTabPage">
        <button class="tabButton" onclick="openMainTab(event, 'Erzeuger') ">Erzeuger</button>
        <button class="tabButton" onclick="openMainTab(event, 'Verbraucher') ">Verbraucher</button>
        <section class="mainTabContent" id="Erzeuger">
                <h3>Erzeuger</h3>)";
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
    s += closeTable();
    return s;
}

string HTMLGenerator::openBody(bool mainPage) {
    if (mainPage)
        return R"(<body onload="openMainTab(event, 'Erzeuger') ">)";
    else
        return R"(<body>)";
}

string HTMLGenerator::closeBody() {
    string body = R"(</body> </html>)";
    return body;
}

string HTMLGenerator::generateTableHead(string& type) {
    string headerText = "";
    if (type == "Erzeuger")
        headerText = "Einspeisung";
    else
        headerText = "Verbrauch";

    string s = R"(<table style="width:100%">)";
    s += "<tr>";
    s += R"(<th>)";
    s += "Typ";
    s += R"(</th>)";
    s += R"(<th>)";
    s += "Name";
    s += R"(</th>)";
    s += R"(<th>)";
    s += "ID";
    s += R"(</th>)";
    s += R"(<th>)";
    s += headerText;
    s += R"(</th>)";
    s += R"(<th>)";
    s += "Zeitpunkt";
    s += R"(</th>)";
    s += R"(</tr>)";
    return s;
}

string HTMLGenerator::generateTableRow(string& type, string name, int id, double value, unsigned long long time) {
    string s;

    s += "<tr>";
    s += "<td>";
    s += type;
    s += R"(</td>)";
    s += "<td>";
    s += name;
    s += R"(</td>)";
    s += "<td>";
    s += to_string(id);
    s += R"(</td>)";
    s += "<td>";
    s += to_string(value);
    s += R"(</td>)";
    s += "<td>";
    //todo cast time to readable string
    s += time;
    s += R"(</td>)";
    s += R"(</tr>)";
    return s;
}

string HTMLGenerator::closeTable() {
    return "</table>";
}