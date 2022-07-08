(ns -clojure.core
  (:use ring.adapter.jetty)
  (:require [ring.util.response :refer [response]])
  (:require [compojure.core :refer [defroutes, POST, GET]])
  (:require [ring.middleware.json] :refer [wrap-json-body, wrap-json-response]))

(defroutes app
  (POST "/api/auth/register" [request] (prn (get-in request [:body "user"]))
    (response "Uploaded user."))
  (POST "/api/auth/login" [request] "login")
  (GET "/api/protected", [request] "protected"))

(defn -main [] #_{:clj-kondo/ignore [:unresolved-symbol]}
  (run-jetty (wrap-json-body app {:port 1337 :join? false})))
