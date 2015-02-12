# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ubuntu/trusty32"
  config.ssh.forward_agent = true
  config.vm.synced_folder "/Users/gadomski/Projects", "/projects"
  config.vm.synced_folder "/Users/gadomski/src", "/src"

  config.vm.provider "virtualbox" do |v|
    v.name = "rivlib-utils-vagrant"
    v.memory = 8192
    v.cpus = 2
  end
end
