#include "authentificator.h"

Authentificator::Authentificator(QObject *parent) : QObject(parent)
{

}

Authentificator::~Authentificator()
{

}

void Authentificator::authentificate(std::string username, std::string password, QByteArray hash)
{

    //JSON data
    //QByteArray data = dataString.c_str();
    QByteArray data = "{\"agent\":{\"name\":\"Minecraft\",\"version\":1},\"username\":\"";
    data.append(username.c_str());
    data.append("\",\"password\":\"");
    data.append(password.c_str());
    data.append("\"}");

    QByteArray response;

    if(sendRequest("https://authserver.mojang.com/authenticate", data, response))
    {
        //From this point, we have the access token in the response, gotta get it
        QByteArray accessToken = getJsonParameter(response, "accessToken");
        QByteArray selectedProfile = getJsonParameter(response, "selectedProfile");

        data = "{\"accessToken\": ";
        data.append(accessToken);
        data.append(",\"selectedProfile\": ");
        data.append(selectedProfile);
        data.append(", \"serverId\": \"");
        data.append(hash);
        data.append("\"}");

        sendRequest("https://sessionserver.mojang.com/session/minecraft/join", data, response);

    }
}

bool Authentificator::sendRequest(QString urlInput, QByteArray data, QByteArray & response)
{
    //Create an access manager
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);

    //Url of the auth server
    QUrl url(urlInput);
    QNetworkRequest request(url);

    //Set it to JSON
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //Json size
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.length());

    //Create loop to wait for response
    QEventLoop eventLoop;

    //quit the loop when request is finished
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    //Get reply
    QNetworkReply *reply = manager->post(request, data);
    eventLoop.exec();
    response = reply->readAll();
    if(reply->error())
    {
        QString error = reply->errorString();
        ui->writeToConsole("Server replied: " + response);
        return false;
    }
    else
    {
        return true;
    }
}

QByteArray Authentificator::getJsonParameter(QByteArray response, QByteArray parameter)
{
    QByteArray output;
    int parameterPosition = response.indexOf(parameter) + parameter.length() + 2;
    //Next two chacaters are ":
    if(response.at(parameterPosition) == '"') //Only one parameter
    {
        int i = 1;
        output.append('"');
        while(response.at(parameterPosition + i)!= '"')
        {
            output.append(response.at(parameterPosition + i));
            i++;
        }
        output.append('"');
    }
    else if(response.at(parameterPosition) == '{')
    {
        int i = 1;
        int nbLeftBrackets = 0;
        output.append('{');
        while(response.at(parameterPosition + i)!= '}' && nbLeftBrackets <= 0)
        {
            if(response.at(parameterPosition + i)== '{')
            {
                nbLeftBrackets++;
            }
            if(response.at(parameterPosition + i)== '}')
            {
                nbLeftBrackets--;
            }
            output.append(response.at(parameterPosition + i));
            i++;
        }
        output.append('}');
    }
    return output;
}
