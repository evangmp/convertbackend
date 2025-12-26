#include <httplib.h>
#include <iostream>

#include "convert.h"

#include <ctime> // Import the ctime library

int main() {
    httplib::Server server;

    // Enable CORS
    server.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "*");
        return httplib::Server::HandlerResponse::Unhandled;
    });

    // Handle OPTIONS requests
    server.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "*");
    });

    // Handle POST requests
    server.Post("/compile", [](const httplib::Request& req, httplib::Response& res) {
        // time
        std::string dateString = convertDateToString();
        std::string nameFile = "new_document_" + dateString;
        
        std::string outputGeneral = R"(C:\\Users\\evang\\Documents\\quizzpr2\\optilearn-front\\public\\)"; // YOUR path
        std::string outputText = outputGeneral + nameFile + ".tex";
        std::string outputPNG = outputGeneral + nameFile + ".png";
        std::string outputPNGCrop = outputGeneral + nameFile + "C.png";
        std::string outputPDF = outputGeneral + nameFile + ".pdf";

        compileLatexToPDF(req.body, outputText, outputGeneral);
        convertPDFToPNG(outputPDF, outputPNG);
        cropPNG(outputPNG, outputPNGCrop);

        // Send a response back to the frontend
        res.set_content(nameFile + "C.png", "text/plain");
    });

    std::cout << "Server is listening on port 9001..." << std::endl;
    server.listen("0.0.0.0", 9001);

    return 0;
}
