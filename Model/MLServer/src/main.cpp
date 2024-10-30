#include "MLServer.hpp"
#include "MLServer_Model.hpp"
#include "mein_nmc.hpp"
#include "Utils.hpp"

// Load Logreg
mlpack::LogisticRegression<> &modelLogreg = get_LogReg();

// Load RandomForest
mlpack::RandomForest<> &modelRF = getRF();

// load tokenizers
mlpack::data::SplitByAnyOf tokenizers(" .,\"");

// Load encoders
mlpack::data::BagOfWordsEncoding<mlpack::data::SplitByAnyOf::TokenType> BOW_encoder = BagOfWordsSplit();
// const DictionaryType &BOW_dictionary = BOW_encoder.Dictionary();
mlpack::data::TfIdfEncoding<mlpack::data::SplitByAnyOf::TokenType> TFID_encoder = TfidSplit();
// const DictionaryType &TFID_dictionary = TFID_encoder.Dictionary();

std::string removecharacters = returnRemoveChars();
std::vector<std::string> stopWords = returnStopWords();

int main()
{
    // Get port
    int port = getPORTenv();

    // Load NMC
    Mein_NMC<arma::sp_mat> &modelNMC = get_NMC_SP();

    // webserver
    uWS::App()
        .get("/", [](uWS::HttpResponse<false> *res, uWS::HttpRequest *req)
        {
            res->writeStatus("200")->end("Welcome to the mlpack uwebsocket model server!\n");
        })
        .post("/", [](uWS::HttpResponse<false> *res, uWS::HttpRequest *req) {
            if(checkCustomheader(req->getHeader("whoami"))){
                std::string jsonData = R"({"error": "who are you??"})";
                res->writeHeader("Content-Type", "application/json")->writeStatus("403")->end(jsonData.data());
                return;
            }
            // checks if it is json
            if (std::string(req->getHeader("content-type")) == "application/json")
            {
                if(checkContentlength(req->getHeader("content-length"))){
                std::string headervalue = R"({"error":"echo - request needs a payload"})";
                res->writeStatus("400")->writeHeader("Content-Type", "application/json")->end(headervalue.data());
                }

                // if JSON and not empty
                res->onData([res](std::string_view data, bool last)
                    {
                        //captured all using references
                        if (last)
                        {

                            std::string value = R"({"success":"JSON - success parsing Json"})";
                            res->writeStatus("200");
                            res->writeHeader("Content-Type", "application/json");
                            res->end(value.data());
                            return;
                        } // if last
                    }); // onData
            } //if headervalue = application/json
            res->onAborted([res](){
                res->writeStatus("500")->end("request aborted");
                return;
            }); // onAborted
        }) // post "/""
        .post("/rf", [](uWS::HttpResponse<false> *res, uWS::HttpRequest *req){
            if(checkCustomheader(req->getHeader("whoami"))){
                std::string jsonData = R"({"error": "who are you??"})";
                res->writeHeader("Content-Type", "application/json")->writeStatus("403")->end(jsonData.data());
                return;
            }
            if (std::string(req->getHeader("content-type")) == "application/json")
            {
                if(checkContentlength(req->getHeader("content-length"))){
                std::string headervalue = R"({"error":"echo - request needs a payload"})";
                res->writeStatus("400")->writeHeader("Content-Type", "application/json")->end(headervalue.data());
                }

                res->onData([res](std::string_view data, bool last){
                    if(last){
                        std::string value(data.data(), data.size());
                        try{
                            Json receivedJson = Json::parse(value);
                            if (receivedJson["rf"].is_null()){
                                //null ffn
                                value = R"({"error":"Invalid JSON - error parsing Json"})";
                                res->writeStatus("400")->writeHeader("Content-Type", "application/json");
                                res->end(value.data());
                                return;
                            }
                            value = receivedJson["rf"];
                            arma::mat valuemat = tfidStringCleaner(value, stopWords,  removecharacters, TFID_encoder.Dictionary(), tokenizers, TFID_encoder, true);
                            scalerTransform(scaler_methods::MINMAX_SCALAR, valuemat);
                            arma::Row<size_t> label;
                            arma::mat prob;
                            modelRF.Classify(valuemat, label, prob);
                            convertRowToResult(label, prob, value);
                            res->writeStatus("200")->writeHeader("Content-Type", "application/json");
                            res->end(value.data());
                            return;
                            // rowToString()
                        }catch (const std::exception &e){
                            std::string errorMessage = "Error: ";
                            errorMessage += e.what();
                            std::string value = R"({"error": ")" + errorMessage + R"("})";
                            res->writeStatus("400")->writeHeader("Content-Type", "application/json");
                            res->end(value.data());
                            return;
                        } //try-catch
                    } //last
                }); //onData
                res->onAborted([res](){
                    res->writeStatus("500")->end("request aborted");
                    return;
                }); // onAborted
            }// if application/json
        })
        .post("/logreg",[](uWS::HttpResponse<false> *res, uWS::HttpRequest *req){
            if(checkCustomheader(req->getHeader("whoami"))){
                std::string jsonData = R"({"error": "who are you??"})";
                res->writeHeader("Content-Type", "application/json")->writeStatus("403")->end(jsonData.data());
                return;
            }
            if (std::string(req->getHeader("content-type")) == "application/json")
            {
                if(checkContentlength(req->getHeader("content-length"))){
                std::string headervalue = R"({"error":"echo - request needs a payload"})";
                res->writeStatus("400")->writeHeader("Content-Type", "application/json")->end(headervalue.data());
                }

                res->onData([res](std::string_view data, bool last){
                    if(last){
                        std::string value(data.data(), data.size());
                        try{
                            Json receivedJson = Json::parse(value);
                            if (receivedJson["logreg"].is_null()){
                                //null ffn
                                value = R"({"error":"Invalid JSON - error parsing Json"})";
                                res->writeStatus("400")->writeHeader("Content-Type", "application/json");
                                res->end(value.data());
                                return;
                            }
                            value = receivedJson["logreg"];
                            arma::mat valuemat = bowStringCleaner(value, stopWords,  removecharacters, BOW_encoder.Dictionary(), tokenizers, BOW_encoder, true);
                            scalerTransform(scaler_methods::MINMAX_SCALAR, valuemat);
                            arma::Row<size_t> label;
                            arma::mat prob;
                            modelLogreg.Classify(valuemat, label, 0.5);
                            modelLogreg.Classify(valuemat, prob);
                            convertRowToResult(label, prob, value);
                            res->writeStatus("200")->writeHeader("Content-Type", "application/json");
                            res->end(value.data());
                            return;
                            // rowToString()
                        }catch (const std::exception &e){
                            std::string errorMessage = "Error: ";
                            errorMessage += e.what();
                            std::string value = R"({"error": ")" + errorMessage + R"("})";
                            res->writeStatus("400")->writeHeader("Content-Type", "application/json");
                            res->end(value.data());
                            return;
                        } //try-catch
                    } //last
                }); //onData
                res->onAborted([res](){
                    res->writeStatus("500")->end("request aborted");
                    return;
                }); // onAborted
            }// if application/json
        })
        .post("/nmc", [&modelNMC](uWS::HttpResponse<false> *res, uWS::HttpRequest *req){
            if(checkCustomheader(req->getHeader("whoami"))){
                std::string jsonData = R"({"error": "who are you??"})";
                res->writeHeader("Content-Type", "application/json")->writeStatus("403")->end(jsonData.data());
                return;
            }
            if(checkContentlength(req->getHeader("content-length"))){
                std::string headervalue = R"({"error":"echo - request needs a payload"})";
                res->writeStatus("400")->writeHeader("Content-Type", "application/json")->end(headervalue.data());
            }

            res->onData([res, &modelNMC](std::string_view data, bool last){
                if(last){
                    std::string value(data.data(), data.size());
                    try{
                        Json receivedJson = Json::parse(value);
                        std::string nmc = receivedJson["nmc"];
                        arma::sp_mat matText(tfidStringCleaner(nmc, stopWords,  removecharacters, TFID_encoder.Dictionary(), tokenizers, TFID_encoder, true));
                    modelpredToString(modelNMC.RPredict(matText), nmc);
                    res->writeStatus("200");
                            res->writeHeader("Content-Type", "application/json");
                            res->end(nmc.data());
                            return;
                    }catch (const std::exception &e){
                        std::string valuev = R"({"error":"Invalid JSON - error parsing Json"})";
                                res->writeStatus("400")->writeHeader("Content-Type", "application/json")->end(valuev.data());
                                return;
                    }//try-catch
                }
            });
            res->onAborted([res](){
                    res->writeStatus("500")->end("request aborted");
                    return;
                }); // onAborted
        })
        .listen("0.0.0.0", port, [port](auto *listen_socket)
        {
            if(listen_socket)
                std::cout << "http://0.0.0.0:" << port << std::endl;
        })
        .run();
    std::cout << "Failed to listen on port " << port << std::endl;
}
