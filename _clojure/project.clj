(defproject _clojure "0.1.0-SNAPSHOT"
  :description "FIXME: write description"
  :url "http://example.com/FIXME"
  :license {:name "EPL-2.0 OR GPL-2.0-or-later WITH Classpath-exception-2.0"
            :url "https://www.eclipse.org/legal/epl-2.0/"}
  :dependencies [[org.clojure/clojure "1.10.3"]
                 [ring/ring-core "1.8.2"] [ring/ring-jetty-adapter "1.8.2"] [compojure "1.7.0"] [ring/ring-json "0.5.1"]]
  :repl-options {:init-ns -clojure.core}
  :main -clojure.core/-main)

