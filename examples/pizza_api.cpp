#include "crow_all.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string orderPizza(const vector<string>& toppings) {
    if (toppings.empty()) {
        return "Cheese Pizza";
    }

    string pizza = "Pizza with ";
    for (size_t i = 0; i < toppings.size(); i++) {
        pizza += toppings[i];
        if (i < toppings.size() - 1) {
            pizza += ", ";
        }
    }
    return pizza;
}

string readFile(const string& filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return crow::response(readFile("pizza_order.html"));
    });

    CROW_ROUTE(app, "/order")
    .methods("POST"_method)
    ([](const crow::request& req) {
        auto data = crow::json::load(req.body);
        if (!data || !data.has("toppings")) {
            return crow::response(400, "Invalid JSON");
        }

        vector<string> toppingList;
        for (const auto& item : data["toppings"]) {
            toppingList.push_back(string(item.s()));
        }

        string pizza = orderPizza(toppingList);
        return crow::response(pizza);
    });

    app.port(18080).multithreaded().run();
}